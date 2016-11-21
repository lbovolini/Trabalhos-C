gcc -c main.c io.c funcoes.c matriz.c aux.c -Wall -O3 
gcc -o p main.o funcoes.o io.o matriz.o aux.o -lm
./p