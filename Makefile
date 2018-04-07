CC=gcc
CFLAGS=-c -Wall -std=c99 -g
LDFLAGS=-lcrypto -lpthread
SOURCES=$(shell find src/ -type f -name '*.c')
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=a.out

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.c.o:
	$(CC) $(CPPFLAGS) $(CFLAGS) $< -o $@

clean:
	rm -f $(EXECUTABLE)
	@find src/ -type f -name '*.o' -exec rm -vf {} \;

test: all
	bash -c "time ./$(EXECUTABLE)"

.PHONY: clean
