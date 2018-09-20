CC = g++

DEVFLAGS = -ggdb -Wall -Wextra -Wpedantic -std=c++14

FLAGS = -Wall -std=c++14


SOURCES = $(wildcard src/*.cpp)

OBJ = $(SOURCES:.cpp=.o)


all: $(OBJ)

	$(CC) $(FLAGS) -o tests.bin $^

dev: $(OBJ)

	$(CC) $(DEVFLAGS) -o tests.bin $^

pather: src/pather.cpp

	$(CC) $(DEVFLAGS) -c -o src/pather.o $^

clean:
	rm $(OBJ)
