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
static int TLB_SIZE = 16;

int main(int argc, char *argv[])
{
	if (argc < 3){
		printf("Missing Argument:\n");
		printf("Usage: ./mmu BACKING_STORE.bin addresses.txt\n");
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
	char phys_mem[FRAME_SIZE][FRAME_SIZE * sizeof(char)];
   	int addr = 0;		//int read from addresses.txt
	char *bin;			//for binary conversion from int	
	char page_bin[9];   //extra char for null terminator
	char offset_bin[9]; //extra char for null terminator
	long page, offset, physical, frame;
	long page_table[256];
	long tlb_table[TLB_SIZE];
	char byte_read;
	int i = 0;
	int page_faults = 0;
	int tlb_entries = 0;
	int tlb_hits = 0;
	int tlb_replace = 0;
	
	memset(page_bin, '\0', sizeof(page_bin));
	memset(offset_bin, '\0', sizeof(offset_bin));
	memset(page_table, -1, sizeof(page_table));
	memset(tlb_table, -1, sizeof(tlb_table));
		
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
		
		//check if page is in TLB table, tlb hit
		frame = -1;
		i = 0;
		while(i < TLB_SIZE && frame == -1){
			if ( tlb_table[i] == page){
				frame = tlb_table[i];
				tlb_hits++;
			}
			i++;
		}
		
		//tlb miss	
		if (frame == -1){
			//get frame number from page table
			if ( page_table[page] == -1){
				page_table[page] = page;
				page_faults++;
				frame = page_table[page];
				//read in 256 bytes from BACKING_STORE.bin
				physical = page * FRAME_SIZE;
				fseek(backing, physical, SEEK_SET);
				fread(&phys_mem[page], sizeof(char), 256, backing);
			}
			else{
				frame = page_table[page];
			}
			
			//update tlb with frame number retrieved from page_table
			//check if tlb has empty space
			if ( tlb_entries < TLB_SIZE ){
				tlb_table[tlb_entries] = page;
				tlb_entries++;
			}
			//if tlb is full, replace using FIFO
			else {
				tlb_table[tlb_replace] = page;
				tlb_replace = (tlb_replace + 1) % TLB_SIZE;
			}
		
		}
		//have looked up address, now read a byte of 
		//data
		
		byte_read = phys_mem[frame][offset];
		printf("%i\n", byte_read);
		fprintf(csv_out,"%d,%ld,%i\n", addr, physical, byte_read);
		
	}
	printf("Page Faults = %d\n", page_faults);
	printf("TLB Hits = %d\n", tlb_hits);
    fclose(log_addr);
	fclose(csv_out);
	fclose(backing);
	
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




