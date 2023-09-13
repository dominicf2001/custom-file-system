CC = clang

CFLAGS = -Wall -Wextra -D_FILE_OFFSET_BITS=64

LDFLAGS = -lfuse3

SOURCES = main.c

OUTPUT = fs

all: $(OUTPUT)

$(OUTPUT): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(OUTPUT) $(LDFLAGS)

clean:
	rm -f $(OUTPUT)
