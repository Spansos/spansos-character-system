CC = g++
CFLAGS = -g -Wall -Werror -pedantic

CPP_FILES = $(wildcard src/*.c)
OBJ_FILES = $(patsubst src/%.c,obj/%.o,$(CPP_FILES))
HEADERS   = $(wildcard src/*.h)

INCLUDENAMES = gtk-4.0 glib-2.0 cairo pango-1.0 harfbuzz gdk-pixbuf-2.0 graphene-1.0
INCLUDES     = $(patsubst %,-I"/usr/include/%",$(INCLUDENAMES))
LIBINCLUDES  = $(patsubst %,-I"/usr/lib/%/include",$(INCLUDENAMES))

LIBNAMES = gtk-4 glib-2.0 gobject-2.0 gio-2.0
LIBS     = $(patsubst %,-l"%",$(LIBNAMES))

.PHONY: clean run

all: bin/main

run: bin/main
	./bin/main

clean:
	rm obj/* -f
	rm bin/* -f

obj/%.o: src/%.c $(HEADERS)
	$(CC) $(INCLUDES) $(LIBINCLUDES) $(CFLAGS) -c $< -o $@

bin/main: $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@