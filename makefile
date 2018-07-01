CC = g++

DEVCFLAGS =  -ggdb -Wall -Wextra -Wpedantic -std=c++14

SOURCES = $(wildcard src/*.cpp)

OBJ = $(SOURCES:.cpp=.o)

tests: $(OBJ)

	$(CC) $(DEVCFLAGS) -o $@.bin $^

pather: src/pather.cpp

	$(CC) $(DEVCFLAGS) -c -o src/pather.o $^

clean:
	rm $(OBJ)
