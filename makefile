CC=gcc
CFLAGS=-I.

INSTALL_PATH=/usr/local/bin/
REPO_LIST_PATH=/usr/share/gapper/

gapper:
	$(CC) gapper.c -o gapper
	mv gapper $(INSTALL_PATH)
	mkdir $(REPO_LIST_PATH)
	touch $(REPO_LIST_PATH).gapperList

clean:
	rm -rf $(REPO_LIST_PATH)
	rm -rf $(REPO_LIST_PATH).gapperList
	rm -rf $(INSTALL_PATH)gapper

install:gapper
uninstall:clean

