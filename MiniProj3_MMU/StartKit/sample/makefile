CC=gcc
CFLAGS= -Wall
DEPS = 	
OBJFILES = struct.o test.o
TARGET = test

all: $(TARGET)
$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES)

clean:
	rm -f $(OBJFILES) $(TARGET) *~