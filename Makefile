CC = clang

CFLAGS = -Wall -Wextra

LDFLAGS = -lfuse3

SOURCES = main.c

OUTPUT = fs

all: $(OUTPUT)

$(OUTPUT): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(OUTPUT) $(LDFLAGS)

clean:
	rm -f $(OUTPUT)
