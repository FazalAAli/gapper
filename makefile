CC=gcc
CFLAGS=-I.

install:gapper

gapper:
	$(CC) gapper.c -o gapper

clean:
	rm -rf gapper	