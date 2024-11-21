CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Wvla -g -I./include

all: main

main: src/bignumber.c src/client.c
	$(CC) $(CFLAGS) -o main src/bignumber.c src/client.c

clean:
	rm -f main
