CFLAGS = -Wall -pedantic -Wextra -Wno-unused-variable
TRASH = esub result*

all:    test

test:	esub


range:	esub.c
	cc $(CFLAGS) $< -o $@

clean:
	rm -f $(TRASH)

