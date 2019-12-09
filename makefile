FILE_OUT = petits-chevaux.exe
COMPILE_FILE = main.c
CFLAGS = -o $(FILE_OUT) -Wall -pedantic
CC=gcc
all: run clean
clean:
	rm -rf *.exe *.o
compile:
	$(CC) -o jeu.o -c jeu.c	
	$(CC) $(CFLAGS) jeu.o $(COMPILE_FILE)
run: compile
	./$(FILE_OUT)