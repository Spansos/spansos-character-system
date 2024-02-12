CC = gcc
CFLAGS = -g -Wall -Werror -pedantic

CPP_FILES = $(wildcard src/*.c)
OBJ_FILES = $(patsubst src/%.c,obj/%.o,$(CPP_FILES))
HEADERS   = $(wildcard src/*.h)

.PHONY: clean run

all: bin/main

run: bin/main
	./bin/main

clean:
	rm obj/* -f
	rm bin/* -f

obj/%.o: src/%.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

bin/main: $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $@