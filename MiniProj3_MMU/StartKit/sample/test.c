#include <math.h>
#include <stdio.h>
#include "page_stack.h"

long long convert(int n);
int main() {
    int n = 6;
	Page* head = NULL;
	Page* tmp = NULL, *tail = NULL;
	
	for (int i = 0; i < n; i++){
		tail = append(&head, i);
	}
	
	Page* itr = head;
	while (itr != NULL){
		printf("%ld, ", itr->frame);
		itr = itr->next;
	}	
	itr = head;
	if (itr == head){
		printf("\nvalid\n");
	}		
	else
		printf("\ninvalid\n");
	
	
	
	//swap tail to head, change tail
	tmp = tail->prev;
	move_page_top(&head, &tail);
	tail = tmp;	
	itr = head;
	printf("\n swap tail to head \n");
	while (itr != NULL){
		printf("%ld, ", itr->frame);
		itr = itr->next;
	}
	
	printf("\nTail: %ld", tail->frame);	
	
	printf("\n");
    return 0;
}
