#include <stdio.h> 
#include <stdlib.h> 
#include "page_stack.h"

Page* append(Page** head, long new_frame){
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
	return new_node;
}

void insert_tail(Page** tail, long new_frame){
	Page* new_node = (Page*) malloc(sizeof(Page));
	new_node->frame = new_frame;
	new_node->prev = *tail;
	new_node->next = NULL;
	(*tail)->next = new_node;
	*tail = new_node;
}


void move_page_top(Page** head, Page** accessed){
	if ((*accessed)->next != NULL)	
		(*accessed)->next->prev = (*accessed)->prev;
	(*accessed)->prev->next = (*accessed)->next;
	
	(*head)->prev = *accessed;
	(*accessed)->next = *head;
	(*accessed)->prev = NULL;
	*head = *accessed;
	
	return;
}

Page* get_tail(Page** head){
	Page* temp = *head;
	
	while (temp->next != NULL)
		temp = temp->next;
	
	return temp;
}


