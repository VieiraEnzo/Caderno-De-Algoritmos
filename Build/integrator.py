#!/usr/bin/env python3
r"""
integrator.py - KACTL-style notebook integrator for the UFRJ ICPC caderno.

Walks ../Algoritmos/ category by category (fixed order), inlines the per-chapter
prose from <cat>/_index.tex (if present), and emits each *.h algorithm as a
\subsection{<filename>} followed by rendered metadata + a minted{cpp} code block.

Algorithm files use a KACTL-style /** ... */ header with optional fields:
    Author, Date, License, Source, Description, Usage, Time, Skip, Status
All fields are optional. Continuation lines (not starting with "Field:") belong
to the previous field. The header is stripped from the code block emitted to the
PDF. Files without a header are rendered verbatim with the filename as the title.

Build modes:
    --skinny  : omit files whose header has `Skip: true`
    --hash    : emit a 6-char MD5 hash in the corner of each algorithm block

Output goes to stdout; warnings go to stderr. Intended to be run from Build/.
"""

import sys
import os
import re
import hashlib
import argparse

# Fixed chapter order. Edit to reorder sections in the PDF.
CHAPTERS = ["Matematica", "Geometria", "Strings", "Grafos",
            "Arvore", "DataStructures", "DP", "Extra"]

ALG_PATH = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "Algoritmos")
ALG_PATH = os.path.normpath(ALG_PATH)

# Fields rendered in the PDF metadata block, in this order.
RENDERED_FIELDS = ["Description", "Usage", "Time"]

# Regex for a field line inside the header:  * Field: value
FIELD_RE = re.compile(r"^\s*\*\s*([A-Za-z]+)\s*:\s*(.*)$")


def parse_header(text):
    """Parse a leading /** ... */ block. Returns (fields_dict, body_without_header)
    or (None, text) if no header is present."""
    # Match a block comment at the very start of the file (allowing leading
    # whitespace/blank lines, but it must be the first non-empty content).
    stripped = text.lstrip()
    if not stripped.startswith("/**"):
        return None, text

    # Find the closing */
    end = text.find("*/", text.find("/**"))
    if end == -1:
        return None, text
    header_block = text[text.find("/**") + 3:end]
    body = text[end + 2:]
    # Preserve a leading newline boundary so the code doesn't merge into prose.
    if not body.startswith("\n"):
        body = "\n" + body

    fields = {}
    current = None
    for line in header_block.split("\n"):
        m = FIELD_RE.match(line)
        if m:
            key = m.group(1).strip()
            val = m.group(2).strip()
            fields[key] = val
            current = key
        else:
            # Continuation line: strip leading " * " or " *" or whitespace.
            cont = re.sub(r"^\s*\*?\s?", "", line)
            if current is None:
                # Lines before any "Field:" (e.g. a top comment) — ignore.
                continue
            if cont.strip() == "" and fields[current] == "":
                continue
            fields[current] = (fields[current] + "\n" + cont).strip("\n")

    return fields, body


def should_skip(fields, skinny):
    """In skinny mode, skip files with Skip: true."""
    if not skinny or not fields:
        return False
    val = fields.get("Skip", "").strip().lower()
    return val in ("true", "yes", "1")


def code_hash(body):
    """KACTL-style 6-char MD5 of code, ignoring whitespace and comments."""
    # Strip line comments and block comments, then collapse whitespace.
    s = body
    s = re.sub(r"/\*.*?\*/", "", s, flags=re.DOTALL)  # block comments
    s = re.sub(r"//[^\n]*", "", s)                    # line comments
    s = re.sub(r"\s+", "", s)                          # all whitespace
    return hashlib.md5(s.encode("utf-8")).hexdigest()[:6]


def tex_escape(s):
    """Escape characters that are special in LaTeX text mode."""
    return (s.replace("\\", r"\textbackslash{}")
             .replace("&", r"\&")
             .replace("%", r"\%")
             .replace("$", r"\$")
             .replace("#", r"\#")
             .replace("_", r"\_")
             .replace("{", r"\{")
             .replace("}", r"\}")
             .replace("~", r"\textasciitilde{}")
             .replace("^", r"\textasciicircum{}"))


def render_field(name, value):
    r"""Render a single field to LaTeX using KACTL-style bold labels (\codeheader).
    Usage is emitted as a small minted block; other fields as bold-labeled text."""
    if name == "Usage":
        return "\\codeheader{Usage}{}\n\\begin{minted}[fontsize=\\footnotesize]{cpp}\n" + value.strip() + "\n\\end{minted}\n"
    # Description / Time / others: bold label + value.
    return "\\codeheader{" + name + "}{" + value.strip() + "}\n"


def render_algorithm(path, filename, skinny, want_hash):
    """Return the LaTeX for one .h file, or None if it should be skipped."""
    with open(path, "r", encoding="utf-8") as f:
        text = f.read()

    fields, body = parse_header(text)

    if should_skip(fields, skinny):
        return None

    title = filename  # keep the .h extension: the subsection title IS the filename.
    out = ["\\algotitle{" + tex_escape(title) + "}"]

    if fields:
        # Render selected metadata fields (bold labels) in order.
        for name in RENDERED_FIELDS:
            if name in fields and fields[name].strip():
                out.append(render_field(name, fields[name]))

    # Horizontal rule separating title/metadata from the code; hash right-aligned on it.
    if want_hash:
        h = code_hash(body if fields else text)
        out.append("\\noindent\\rule{\\linewidth}{0.4pt}\\vspace{-1.6em}\\hfill\\texttt{\\tiny " + h + "}\\par")
    else:
        out.append("\\noindent\\rule{\\linewidth}{0.4pt}")

    # Code block (header stripped when present).
    out.append("\\begin{minted}{cpp}")
    if fields:
        out.append(body.strip("\n"))
    else:
        # Legacy file: render verbatim, filename as title.
        sys.stderr.write("WARNING: no header in %s\n" % path)
        out.append(text.strip("\n"))
    out.append("\\end{minted}")

    out.append("")
    return "\n".join(out)


def collect_algorithms(category_dir):
    """Recursively collect *.h files (skipping rem/ subdirs), sorted by filename."""
    files = []
    for root, dirs, names in os.walk(category_dir):
        # Skip rem/ directories at any depth.
        dirs[:] = [d for d in dirs if d != "rem"]
        for n in names:
            if n.endswith(".h"):
                files.append((n, os.path.join(root, n)))
    files.sort(key=lambda p: p[0].lower())
    return files


def main():
    parser = argparse.ArgumentParser(description="Integrate Algoritmos/ into biblioteca.tex")
    parser.add_argument("--skinny", action="store_true",
                        help="Omit files whose header has Skip: true")
    parser.add_argument("--hash", action="store_true",
                        help="Emit 6-char MD5 hash in corner of each algorithm")
    args = parser.parse_args()

    # 1. Emit preamble (preamble.tex contains \begin{document} + titlepage + \begin{multicols}{3}).
    preamble = os.path.join(os.path.dirname(os.path.abspath(__file__)), "preamble.tex")
    with open(preamble, "r", encoding="utf-8") as f:
        sys.stdout.write(f.read())
    sys.stdout.write("\n")

    # 2. Each chapter.
    for cat in CHAPTERS:
        cat_dir = os.path.join(ALG_PATH, cat)
        if not os.path.isdir(cat_dir):
            sys.stderr.write("WARNING: category dir missing: %s\n" % cat_dir)
            continue

        # Inline _index.tex if it exists (it has \section{...} + prose).
        index_tex = os.path.join(cat_dir, "_index.tex")
        if os.path.isfile(index_tex):
            with open(index_tex, "r", encoding="utf-8") as f:
                sys.stdout.write(f.read())
            sys.stdout.write("\n\n")
        else:
            sys.stderr.write("WARNING: no _index.tex in %s; emitting bare section\n" % cat)
            sys.stdout.write("\\section{" + cat + "}\n\n")

        sys.stderr.write("=== %s ===\n" % cat)
        # Algorithms, sorted by filename.
        for fname, fpath in collect_algorithms(cat_dir):
            block = render_algorithm(fpath, fname, args.skinny, args.hash)
            if block is None:
                sys.stderr.write("  [skip] %s\n" % fname)
                continue
            sys.stdout.write(block)
            sys.stderr.write("  %s\n" % fname)

    # 3. Close document.
    sys.stdout.write("\\end{multicols}\n")
    sys.stdout.write("\\end{document}\n")


if __name__ == "__main__":
    main()
