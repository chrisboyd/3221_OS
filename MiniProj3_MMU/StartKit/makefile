CC=gcc
CFLAGS=-I.
DEPS = 	

%.o: %.c &(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

mmu: mmu.o
	$(CC) -o mmu mmu.o 