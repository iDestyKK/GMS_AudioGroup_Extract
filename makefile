CC     = gcc
CFLAGS = --std=gnu89 -O3

all: extract

extract: extract.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) extract
