#include <stdio.h> 
#include <stdlib.h> 
#include "struct.h"

void append(Page** head, long new_frame){
	Page* new_node = (Page*) malloc(sizeof(Page));
	Page* temp = *head;
	new_node->frame = new_frame;
	new_node->next = NULL;
	
	if ( *head == NULL ){
		new_node->prev = NULL;
		*head = new_node;
	}
	else{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_node;
		new_node->prev = temp;
	}
	return;
}

void swap_pages(Page** top, Page** bottom){
	Page* temp_top = *top;
	(*top)->next = (*bottom)->next;
	(*top)->prev = (*bottom)->prev;
	(*bottom)->next = temp_top->next;
	(*bottom)->prev = temp_top->prev;
	*top = *bottom;	
	*bottom = temp_top;
	return;
}


