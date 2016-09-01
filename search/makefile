CC=gcc
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=main.c read_file/read_file.c compressed_prefix_tree/compressed_prefix_tree.c tests/tests.c
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=prefix_tree

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@