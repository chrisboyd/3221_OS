#include <math.h>
#include <stdio.h>
#include "page_stack.h"

long long convert(int n);
int main() {
    int n = 6;
	Page* head = NULL;
	Page* tmp = NULL;
	Page* tail = NULL;
	
	for (int i = 0; i < n; i++){
		append(&head, i);
	}
	printf("pre swap:\n");
	Page* itr = head;
	while (itr != NULL){
		if (itr->next == NULL)
			tmp = itr;
		printf("%ld, ", itr->frame);
		itr = itr->next;
		
	}
	printf("\n");
	move_page_top(&head, &tmp);
	printf("post swap1:\n");

	itr = head;
	while (itr != NULL){
		printf("%ld, ", itr->frame);
		itr = itr->next;
	}
	
	tmp = head->next->next;
	
	move_page_top(&head, &tmp);
	printf("\npost swap2 and add tail:\n");
	tail = get_tail(&head);
	insert_tail(&tail, 55);
	itr = head;
	while (itr != NULL){
		printf("%ld, ", itr->frame);
		itr = itr->next;
	}
	printf("\n");
	
	//printf("idexing?: %ld, %ld\n", head[0].frame, head[1].frame);	
    /*
	printf("Enter a decimal number: ");
    scanf("%d", &n);
    printf("%d in decimal = %lld in binary", n, convert(n));
	*/
    return 0;
}

long long convert(int n) {
    long long bin = 0;
    int rem, i = 1, step = 1;
    while (n != 0) {
        rem = n % 2;
        printf("Step %d: %d/2, Remainder = %d, Quotient = %d\n", step++, n, rem, n / 2);
        n /= 2;
        bin += rem * i;
        i *= 10;
    }
    return bin;
}