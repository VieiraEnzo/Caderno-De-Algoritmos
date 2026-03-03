g++ -std=c++17 -o getlatex getlatex.cpp -O2
./getlatex $1 > biblioteca.tex
rubber -d --shell-escape biblioteca
mv biblioteca.pdf ../Pdf
# rm tmp.cpp
rm getlatex biblioteca.aux biblioteca.toc biblioteca.out
rm -f biblioteca.rubbercache
rm biblioteca.log