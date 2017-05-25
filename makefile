all: project

main.o: main.c
	gcc -std=c99 -m32 -c -o main.o main.c

func.o: funcs.asm
	nasm -f elf32 -o funcs.o funcs.asm

project: main.o func.o
	gcc -o project main.o funcs.o

clean:
	rm -rf *.o project