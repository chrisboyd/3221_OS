Usage
--------
$./test.sh 
This will compile and run the program with both of the 256 frame and 128 frame size page tables.

To run outside of the test script use:
$make
$./mmu BACKING_STORE.bin addresses.txt 128 //for 128 frame
OR
$./mmu BACKING_STORE.bin addresses.txt 256 //for 256 frame

Notes
--------
1) Physical address (column 2 of output.csv) is the combination of the
frame and the offset determined from the logical address (column 1).
My implementation uses this as memory[frame][offset] in an array with
256 indices of 256 bytes of data. To write a single number in the 
output.csv file I used (frame*1000) + offset as no format was specified.

2) The project description does not specify which LRU algorithm to use. 
I chose to implement the Stack method from Ch 10.4. To facilitate this, the
entire page table is a doubly-linked list for both 128 and 256 page table sizes.

I wasn't sure if the LRU-Approximation Algorithms were valid. 
