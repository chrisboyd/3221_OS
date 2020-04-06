#!/bin/bash -e
echo "Cleaning"
make clean
echo "Compiling"
make
echo "***************************"
echo "Running 128 page table size"
./mmu BACKING_STORE.bin addresses.txt 128 
sleep 0.25s
echo "***************************"
echo "Running 256 page table size" 
./mmu BACKING_STORE.bin addresses.txt 256 
echo "***************************"

