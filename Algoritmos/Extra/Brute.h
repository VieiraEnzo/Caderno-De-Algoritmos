/**
 * Description: Script bash para stress testing. Compila code, brute e gen,
 *     gera testes com seeds crescentes e compara as saídas com \texttt{diff}.
 *     Para no primeiro WA e imprime o caso falho.
 * Time: N/A
 * Status: tested
 */

set -e
g++ code.cpp -o code
g++ brute.cpp -o brute
g++ gen.cpp -o gen
for((i = 1; ; ++i)) do
    echo "Test: " $i
    ./gen $i > input_file
    cat input_file
    ./code < input_file > myAnswer
    ./brute < input_file > correctAnswer
    diff -Z myAnswer correctAnswer > /dev/null || break
    cat input_file
    cat myAnswer
    cat correctAnswer
    echo "Passed test" $i
done
echo "WA:"
cat input_file
echo "My:"
cat myAnswer
echo "correct:"
cat correctAnswer