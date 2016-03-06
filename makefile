#Bradley Taniguchi

all: main.o clean

main.o: main.c
	gcc main.c -o main.o

clean:
