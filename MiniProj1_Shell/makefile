CC=gcc
CFLAGS=-I.
DEPS = 	

%.o: %.c &(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

boyd-shell: boyd-shell.o
	$(CC) -o boyd-shell boyd-shell.o 