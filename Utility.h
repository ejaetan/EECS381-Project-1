#include <stdlib.h>
#include "Person.h"


#define MAX_CHAR 64
#define INPUT_FORMAT "%63s"

/* global variable declarations for this module */
extern int g_string_memory;				/* number of bytes used in C-strings */
extern int g_Container_count;			/* number of Ordered_containers currently allocated */
extern int g_Container_items_in_use;	/* number of Ordered_container items currently in use */
extern int g_Container_items_allocated;	/* number of Ordered_container items currently allocated */
extern int g_Meeting_memory;            /* number of meeting struct */


/* Your own decleration and definitions */
void skip_type_ahead(void);
void* malloc_with_error_handling(size_t ptr);
//int compare_Person_lastname(struct Person *Person1, struct Person *Person2);
int time_conversion(int time);

/* Error message function */
void couldnt_open_file_msg(void);
void invalid_data_msg(void);


