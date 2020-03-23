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

static int FRAME_SIZE = 256;

int main(int argc, char *argv[])
{
	if (argc < 3){
		printf("Missing Argument:\n");
		printf("Usage: ./mmu file.bin addresses.txt\n");
		return -1;
	}
	
    FILE *log_addr;
	FILE *csv_out;
	FILE *backing;
    log_addr = fopen(argv[2],"r");
	csv_out = fopen("output.csv", "w");
	backing = fopen("BACKING_STORE.bin", "rb");
	if (log_addr == NULL){
		printf("Could not open: %s\n", argv[2]);
		return -1;
	}
	if (csv_out == NULL){
		printf("Could not open output.csv\n");
		return -1;
	}
   	int addr = 0;
	char *bin;
	char page_bin[9];
	char offset_bin[9];
	long page, offset, physical;
	long page_table[256];
	char byte_read;
	int j = 0;
	
	memset(page_bin, '\0', sizeof(page_bin));
	memset(offset_bin, '\0', sizeof(offset_bin));
	memset(page_table, 0, sizeof(page_table));
	
	while ( fscanf(log_addr, "%d", &addr) != EOF){
		//get full binary of first address		
		bin = int2bin(addr);
		//get binary of the page number
		strncpy(page_bin, bin, 8);
		//get binary of the offset
		strncpy(offset_bin, bin + 8, 8);
		//convert binary page number and offset to decimal
		page = strtol(page_bin, NULL, 2);
		offset = strtol(offset_bin, NULL, 2);
		if ( page_table[page] == 0){
			page_table[page] = page;
		}
		fseek(backing, physical, SEEK_SET);
		fread(&byte_read, sizeof(char), 1, backing);
		physical = page * FRAME_SIZE + offset;
		/*
		printf("logical: %d, ", addr);
		printf("page: %ld, ", page);
		printf("offset: %ld, ", offset);
		printf("physical: %ld, ", physical);
		*/
		printf("%i\n", byte_read);
	}
	
    fclose(log_addr);
    return 0;
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




