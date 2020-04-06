CC=gcc
CFLAGS= -Wall
DEPS = 	
OBJFILES = page_stack.o test.o
TARGET = test

all: $(TARGET)
$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES)

clean:
	rm -f $(OBJFILES) $(TARGET) *~