typedef struct Page_list{
	long frame;
	struct Page_list* prev;
	struct Page_list* next;
}Page;

void append(Page** head, long new_frame);
void move_page_top(Page** top, Page **accessed);
Page* get_tail(Page** head);
void insert_tail(Page** tail, long new_frame);

