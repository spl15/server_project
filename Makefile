# Makefile for project 1. will make use of make to create the client and serevr excutiables, and Make clean
# to clean all .o and executables.
OBJECTS = httpServer.o httpClient.o
CFLAGS = -g -c -Wall
CC = gcc


all: $(OBJECTS)
	$(CC) httpServer.o -o server
	$(CC) httpClient.o -o client

httpClient.o: httpClient.c
	$(CC) $(CFLAGS) httpClient.c

httpServer.o: httpServer.c
	$(CC) $(CFLAGS) httpServer.c



clean:
	$(RM) *o *gch server client
