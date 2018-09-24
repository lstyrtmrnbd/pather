CC = g++

DEVFLAGS = -ggdb -Wall -Wextra -Wpedantic -std=c++14

FLAGS = -Wall -std=c++14

SFML = -lsfml-graphics -lsfml-window -lsfml-system


SOURCES = $(wildcard src/*.cpp)

OBJ = $(SOURCES:.cpp=.o)


all: $(OBJ)

	$(CC) $(FLAGS) -o tests.bin $^ $(SFML)

dev: $(OBJ)

	$(CC) $(DEVFLAGS) -o tests.bin $^ $(SFML)

pather: src/pather.cpp

	$(CC) $(DEVFLAGS) -c -o src/pather.o $^

clean:
	rm $(OBJ)
