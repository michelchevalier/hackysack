
# Small. Unbreakable. Rational. Fast.$
# This program is public domain.$
# Author: Michel Chevalier (2015)$
# Makefile

OBJECTS := fs.o admin_html.o stack.o default_config.o misc.o trie.o

hackysack: $(OBJECTS)
	gcc hackysack.c $(OBJECTS) -o hackysack

admin_html.c: admin.html
	cp admin.html admin_html.c

all: hackysack

clean:
	rm -f $(OBJECTS) hackysack admin_html.c
