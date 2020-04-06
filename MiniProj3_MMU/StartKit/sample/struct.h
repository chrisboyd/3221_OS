typedef struct Page_list{
	long frame;
	struct Page_list* prev;
	struct Page_list* next;
}Page;

void append(Page** head, long new_frame);
void swap_pages(Page** top, Page **bottom);
