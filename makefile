CC = gcc
CFLAGS = -Wall
OBJ = dll.o

all: interactive sample

interactive: $(OBJ) interactive.o
	$(CC) $(CFLAGS) $^ -o $@

sample: $(OBJ) sample.o
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean:
	rm -f interactive sample *.o
