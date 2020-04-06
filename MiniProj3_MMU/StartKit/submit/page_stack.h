//struct representing a page in the page table
typedef struct Page_list {
	long frame;
	struct Page_list *prev;
	struct Page_list *next;
} Page;

/*******
 *create a new Page with new_frame and add it to the
 *end of the list pointed at by head 
 *******/
Page* append(Page **head, long new_frame);
/*******
 *move accessed to the position pointed at by top,
 *updates top to look at the new head of the list
 *******/
void move_page_top(Page **top, Page **accessed);

/*******
 *get a pointer to the end of the list pointed at by
 *head 
 *******/
Page* get_tail(Page **head);

