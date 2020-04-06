CC=gcc
CFLAGS= -Wall
DEPS = 	
OBJFILES = page_stack.o mmu.o
TARGET = mmu

all: $(TARGET)
$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES)

clean:
	rm -f $(OBJFILES) $(TARGET) *~