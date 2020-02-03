# Makefile for project 1. will make use of make all to create executable named hash,
# Make run to fully run the program, make test to incrementaly test the program, and Make clean
# to clean all .o and executables.
OBJECTS = echo_server.o echo_client.o
CFLAGS = -g -c -Wall
CC = gcc


all: $(OBJECTS)
	$(CC) echo_server.o -o server
	$(CC) echo_client.o -o client

echo_client.o: echo_client.c
	$(CC) $(CFLAGS) echo_client.c

echo_server.o: echo_server.c
	$(CC) $(CFLAGS) echo_server.c



clean:
	$(RM) *o *gch server client
