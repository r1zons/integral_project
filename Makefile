CC = gcc
FLAGS = -Wall -Wextra -Werror -m32

all: main_part.o main_asm.o
	$(CC) $(FLAGS) main_part.o main_asm.o -o main

main_asm.o: main_asm.asm
	nasm -f elf32 main_asm.asm

main.o: main_part.c
	$(CC) $(FLAGS) main_part.c -c

test: main_part.o main_asm.o
	$(CC) $(FLAGS) main_part.o main_asm.o -o test
	./test
