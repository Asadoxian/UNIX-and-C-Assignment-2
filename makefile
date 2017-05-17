CC=gcc
CFLAGS=-I. -g -Wall
DEPS = io.h files.h logger.h
OBJ = io.o files.o logger.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

AssignmentMake: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

.PHONY:clean

clean:
	-rm edit$(OBJ)
