#!/bin/bash -e
echo "Cleaning"
make clean
echo "Compiling"
make
echo "Running"
./mmu BACKING_STORE.bin addresses.txt 256 > out_256.txt
echo "Comparing"
diff out_256.txt correct.txt
