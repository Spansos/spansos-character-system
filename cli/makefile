CC       := gcc
CFLAGS   := -g -Wall -Werror -pedantic
PACKAGES := libpng

CPP_FILES := $(wildcard src/*.c)
OBJ_FILES := $(patsubst src/%.c,obj/%.o,$(CPP_FILES))
HEADERS   := $(wildcard src/*.h)

LIBS   := $(shell pkg-config --libs $(PACKAGES))
CFLAGS += $(shell pkg-config --cflags $(PACKAGES))

.PHONY: clean run

all: bin/main.out

run: bin/main.out
	./bin/main.out

clean:
	rm obj/* -f
	rm bin/* -f

obj/%.o: src/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

bin/main.out: $(OBJ_FILES)
	$(CC) $(CFLAGS) $(LIBS) $^ -o $@