CC = clang

CFLAGS = -Wall -Wextra -D_FILE_OFFSET_BITS=64

LDFLAGS = -lfuse3

SOURCES = main.c

OUTPUT = fs

TEST_OUTPUT = test

all: clean $(OUTPUT)

$(OUTPUT): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(OUTPUT) $(LDFLAGS)

test: clean test.c
	$(CC) $(CFLAGS) test.c b_tree.c -o $(TEST_OUTPUT)

clean:
	rm -f $(OUTPUT) $(TEST_OUTPUT)
