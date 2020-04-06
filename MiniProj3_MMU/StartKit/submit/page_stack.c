#include <stdio.h> 
#include <stdlib.h> 
#include "page_stack.h"

/*******
 *create a new Page with new_frame and add it to the
 *end of the list pointed at by head 
 *******/
Page* append(Page **head, long new_frame) {
	Page *new_node = (Page*) malloc(sizeof(Page));
	Page *temp = *head;
	new_node->frame = new_frame;
	new_node->next = NULL;

	//head points to an empty list
	if (*head == NULL) {
		new_node->prev = NULL;
		*head = new_node;
	}
	//go to the end of the list an
	else {
		while (temp->next != NULL)
			temp = temp->next;
		//add new Page to the end
		temp->next = new_node;
		new_node->prev = temp;
	}
	return new_node;
}

/*******
 *move accessed to the position pointed at by top,
 *updates top to look at the new head of the list
 *******/
void move_page_top(Page **head, Page **accessed) {
	//Ensure accessed is not the end of the list
	if ((*accessed)->next != NULL)
		(*accessed)->next->prev = (*accessed)->prev;
	(*accessed)->prev->next = (*accessed)->next;

	(*head)->prev = *accessed;
	(*accessed)->next = *head;
	(*accessed)->prev = NULL;
	//update head to point at the new head of the list
	*head = *accessed;

	return;
}

/*******
 *get a pointer to the end of the list pointed at by
 *head 
 *******/
Page* get_tail(Page **head) {
	Page *temp = *head;

	while (temp->next != NULL)
		temp = temp->next;

	return temp;
}

