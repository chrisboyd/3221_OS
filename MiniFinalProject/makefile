CC=gcc
CFLAGS= -Wall -g
DEPS = 	
OBJFILES = DiskScheduler.o DiskAlgorithms.o
TARGET = disk_sched

all: $(TARGET)
$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES)

clean:
	rm -f $(OBJFILES) $(TARGET) *~