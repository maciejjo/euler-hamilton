CC = gcc
CFLAGS = -Wall -std=gnu99 -O3 -pedantic

euler-hamilton: main.c graph.c list.c arrays.c
	$(CC) $(CFLAGS) main.c graph.c list.c arrays.c -o euler-hamilton
