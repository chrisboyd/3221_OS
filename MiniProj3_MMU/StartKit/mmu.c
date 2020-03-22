/****
 * Name: Christopher Boyd
 * St #: 216 869 356
 * York: chris360
 * 
 * 
 * 
 ****/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mmu.h"

unsigned int mask = 11111111;

int main(int argc, char *argv[])
{
	if (argc < 3){
		printf("Missing Argument:\n");
		printf("Usage: ./mmu file.bin addresses.txt\n");
		exit(1);
	}
	
    FILE *log_addr;
    log_addr = fopen(argv[2],"r");
   	int addr = 0;
	int j = 0;
	
	int offset = 0;
	int page = 0;
	
	while (j < 10){
		fscanf(log_addr, "%d", &addr);
		//char *bin = int2bin(addr);
		printf("%d -> %s\n", addr, bin);
		
		j++;
	}

    fclose(log_addr);


    return 0;
}

int bin2dec(int n){
	int temp = n;
	int dec = 0;
	int base = 1;
}
int dec2bin(int n){
	
}
/*
char *int2bin(int n) {
    int nbits = sizeof(n) * 8;
    char *s = malloc(nbits+1);  
    s[nbits] = '\0';
    unsigned int u = *(unsigned int*)&n;
    int i;
    unsigned int mask = 1 << (nbits-1); 
	// fill in values right-to-left
    for (i = 0; i < nbits; i++, mask >>= 1)
        s[i] = ((u & mask) != 0) + '0';
    return s;
}
*


