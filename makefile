CC=gcc
CFLAGS=-I.

INSTALL_PATH=/usr/local/bin/

gapper:
	$(CC) gapper.c -o gapper
	mv gapper $(INSTALL_PATH)

clean:
	rm -rf $(INSTALL_PATH)gapper

install:gapper
uninstall:clean

