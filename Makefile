CC = gcc
CFLAGS = -Wall -std=gnu99 -O3 -pedantic

graph-algorithms: main.c graph.c
	$(CC) $(CFLAGS) main.c graph.c list.c -o graph-algorithms
