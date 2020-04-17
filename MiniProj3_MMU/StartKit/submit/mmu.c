/****
 * Name: Christopher Boyd
 * St #: 216 869 356
 * York: chris360
 * 
 * Simple Virtual Memory Unit
 *  
 * 
 ****/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "mmu.h"
#include "page_stack.h"

static int FRAME_SIZE = 256;
static int TLB_SIZE = 16;

int main(int argc, char *argv[]) {
	char phys_mem[FRAME_SIZE][FRAME_SIZE * sizeof(char)];
	int addr = 0;		//int read from addresses.txt
	char *bin;			//for binary conversion from int	
	char page_bin[9];   //extra char for null terminator
	char offset_bin[9]; //extra char for null terminator
	long page, offset, physical, frame;
	Page *page_table_head = NULL;
	Page *itr = page_table_head;
	long tlb_table[TLB_SIZE];
	long page_table_size;
	char byte_read;
	int i = 0;
	int page_faults = 0;
	int page_entries = 0;
	int tlb_entries = 0;
	int tlb_hits = 0;
	int tlb_replace = 0;
	double addr_read = 0.0;

	if (argc < 4) {
		printf("Missing Argument:\n");
		printf("Usage: ./mmu BACKING_STORE.bin addresses.txt 128|256\n");
		return -1;
	}

	page_table_size = strtol(argv[3], NULL, 10);
	if (page_table_size != 128 && page_table_size != 256) {
		printf("%ld is an invalid page table size. Choose 128 or 256\n",
				page_table_size);
		return -1;
	}

	FILE *log_addr;
	FILE *csv_out;
	FILE *backing;
	backing = fopen(argv[1], "rb");
	log_addr = fopen(argv[2], "r");
	csv_out = fopen("output.csv", "w");

	//attempt to open all necessary input/outpu files
	if (backing == NULL) {
		printf("Could not open: %s\n", argv[1]);
		return -1;
	}
	if (log_addr == NULL) {
		printf("Could not open: %s\n", argv[2]);
		return -1;
	}
	if (csv_out == NULL) {
		printf("Could not open output.csv\n");
		return -1;
	}

	memset(page_bin, '\0', sizeof(page_bin));
	memset(offset_bin, '\0', sizeof(offset_bin));
	memset(tlb_table, -1, sizeof(tlb_table));

	while (fscanf(log_addr, "%d", &addr) != EOF) {
		addr_read++;
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
		while (i < TLB_SIZE && frame == -1) {
			if (tlb_table[i] == page) {
				frame = tlb_table[i];
				tlb_hits++;
			}
			i++;
		}
		//tlb miss	
		if (frame == -1) {
			//find if page is in page table
			itr = page_table_head;
			if (itr != NULL) {
				while (itr != NULL && frame == -1) {
					if (itr->frame == page) {
						frame = itr->frame;
						//found page, bring to top of stack
						//if not already top
						if (itr != page_table_head)
							move_page_top(&page_table_head, &itr);
					}
					itr = itr->next;
				}
			}

			if (frame == -1) {
				//page fault, read 256 bytes from BINARY_STORE.bin to phys mem
				page_faults++;
				physical = page * FRAME_SIZE;
				fseek(backing, physical, SEEK_SET);
				fread(&phys_mem[page], sizeof(char), 256, backing);

				//table is not full, add 'page' to end of page table
				if (page_entries < page_table_size) {
					append(&page_table_head, page);
					frame = page;
					page_entries++;
				} else {
					//page table is full, use LRU to replace page
					//replace tail, and move new pageto the top as
					//it is most recently referenced
					itr = get_tail(&page_table_head);
					move_page_top(&page_table_head, &itr);
					frame = page;
				}
			}

			//update tlb with frame number 
			//check if tlb has empty space
			if (tlb_entries < TLB_SIZE) {
				tlb_table[tlb_entries] = page;
				tlb_entries++;
			}
			//tlb is full, replace using FIFO, circular array of element
			//to replace
			else {
				tlb_table[tlb_replace] = page;
				tlb_replace = (tlb_replace + 1) % TLB_SIZE;
			}

		}
		//have looked up address, now read a byte of data
		byte_read = phys_mem[frame][offset];
		//output logical address, physical address, byte read to 
		//output.csv
		fprintf(csv_out, "%d,%ld,%i\n", addr, (frame * 1000) + offset,
				byte_read);
	}
	//statistics of page faults and TLB hits
	printf("Page Faults = %.2f%%\n", (page_faults/addr_read)*100);
	printf("TLB Hits = %d\n", tlb_hits);

	//close input/output files
	fclose(log_addr);
	fclose(csv_out);
	fclose(backing);

	return 0;
}

/***********
 * 
 * Convert integer, n, to a binary string.
 * 
 * Note: only returns the lowest 16 bits as that is
 * all that is needed for the page number and offset
 **********/
char* int2bin(int n) {
	int nbits = 16; //since only concerned with the offset and page
	char *s = malloc(nbits + 1);
	s[nbits] = '\0';
	unsigned int u = *(unsigned int*) &n;
	int i;
	unsigned int bit_mask = 1 << (nbits - 1);
	// fill in values right-to-left
	for (i = 0; i < nbits; i++, bit_mask >>= 1) {
		if (u & bit_mask)
			s[i] = '1';
		else
			s[i] = '0';
	}
	return s;
}

