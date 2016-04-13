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
void* malloc_with_error_handling(size_t ptr);


/* Error message function */
void couldnt_open_file_msg(void);
void invalid_data_msg(void);