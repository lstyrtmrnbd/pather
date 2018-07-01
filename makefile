CC = g++

DEVCFLAGS =  -ggdb -Wall -Wextra -Werror -Wpedantic -std=c++14

TARGET = caster

SOURCES = $(wildcard src/*.cpp)

OBJ = $(SOURCES:.cpp=.o)

tests: $(OBJ)

	$(CC) $(DEVCFLAGS) -o $@.bin $^ $(LDFLAGS)

clean:
	rm $(OBJ)
