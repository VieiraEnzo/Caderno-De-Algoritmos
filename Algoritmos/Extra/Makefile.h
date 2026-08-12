/**
 * Description: Template de Makefile com warnings e sanitizers para
 *     programação competitiva.
 * Usage:
 *     \texttt{make a}
 * Time: N/A
 * Status: tested
 */

WARNINGS := -Wshift-overflow=2 -Wfloat-equal -Wconversion
SANITIZERS := -fsanitize=address -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -fsanitize=undefined
a.out: a.cpp
	g++ -Dlocal $(WARNINGS) $(SANITIZERS) a.cpp