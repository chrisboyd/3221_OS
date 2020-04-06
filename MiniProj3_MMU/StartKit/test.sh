#!/bin/bash -e
echo "Compiling"
gcc mmu.c -o mmu
echo "Running 128 page frames"
./mmu BACKING_STORE.bin addresses.txt 128 > out_128.txt
echo "Comparing"
diff out_128.txt correct.txt
