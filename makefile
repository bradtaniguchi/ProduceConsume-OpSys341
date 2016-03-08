#Bradley Taniguchi

all: buffer_incomplete.o

buffer_incomplete.o: buffer_incomplete.c
	gcc buffer_incomplete.c -lpthread -o buffer_incomplete.o

clean: 
	rm -f buffer_incomplete.o
