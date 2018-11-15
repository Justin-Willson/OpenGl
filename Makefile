LDLIBS=-lGL -lGLEW -lSDL2
all: firstGL
clean:
	rm -f *.o firstGL
.PHONY: all clean