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
#include <math.h>
#include "mmu.h"

//unsigned int mask = 11111111;

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
	char *bin;
	char page_bin[9];
	char offset_bin[9];
	char *eptr;
	long page, offset;
	memset(page_bin, '\0', sizeof(page_bin));
	memset(offset_bin, '\0', sizeof(offset_bin));
	
	while (j < 10){
		fscanf(log_addr, "%d", &addr);
		bin = int2bin(addr);
		printf("%d -> %s\n", addr, bin);
		strncpy(page_bin, bin, 8);
		strncpy(offset_bin, bin + 8, 8);
		printf("page\t %s\n", page_bin);
		printf("offset\t\t %s\n", offset_bin);
		page = strtol(page_bin, &eptr, 2);
		offset = strtol(offset_bin, &eptr, 2);
		printf("page: %ld\n", page);
		printf("offset: %ld\n", offset);
		j++;
	}
	printf("256 binary: %ld", bin2dec(bin) );
    fclose(log_addr);
    return 0;
}

int get_offset(char *n){
	int offset = 0;
	unsigned int bit_mask = 1;
	return 0;
}

int get_page(char *n){
	
}

long bin2dec(char *n){
	int decimalnum = atol("100000000"), temp = 0, remainder;
 /* 
    while (binarynum!=0)
    {
        remainder = binarynum % 10;
        binarynum = binarynum / 10;
        decimalnum = decimalnum + remainder*pow(2,temp);
        temp++;
    }
	*/
    return decimalnum;
}

char *int2bin(int n) {
    int nbits = 16; //since only concerned with the offset and page
    char *s = malloc(nbits+1);  
    s[nbits] = '\0';
    unsigned int u = *(unsigned int*)&n;
    int i;
    unsigned int bit_mask = 1 << (nbits-1); 
	// fill in values right-to-left
    for (i = 0; i < nbits; i++, bit_mask >>= 1){
    	if (u & bit_mask)
			s[i] = '1';
		else
			s[i] = '0';
    }    
    return s;
}




