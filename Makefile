LDLIBS=-lGL -lGLEW -lSDL2
CC = g++
CFLAGS  = -g -Wall 

all: firstGL.o display.o
	$(CC) $(CFLAGS) firstGL.o display.o -o output $(LDLIBS)

firstGL.o : firstGL.cpp
	$(CC) $(CFLAGS) -c firstGL.cpp $(LDLIBS)

display.o: display.cpp display.h
	$(CC) $(CFLAGS) -c display.cpp $(LDLIBS)

