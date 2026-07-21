#!/usr/bin/env bash
# Build the ICPC notebook PDF from Algoritmos/ + per-chapter _index.tex prose.
# Run from this directory. Flags are forwarded to integrator.py:
#   --skinny  : omit algorithms whose header has `Skip: true`
#   --hash    : emit 6-char MD5 hash in the corner of each algorithm
set -e

python3 integrator.py "$@" > biblioteca.tex
rubber -d --shell-escape biblioteca
mv biblioteca.pdf ../Pdf/

# Clean up auxiliary files.
rm -f biblioteca.aux biblioteca.toc biblioteca.out biblioteca.log biblioteca.rubbercache
