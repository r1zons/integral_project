.PHONY: all clean

all: test

clean:
	rm *.o

main_part.o: main_part.c
	gcc -c -m32 main_part.c -o main_part.o

main_asm.o: main_asm.asm
	nasm -f elf32 main_asm.asm -o main_asm.o

test: main_part.o main_asm.o
	gcc -m32 main_part.o main_asm.o -lm -o test