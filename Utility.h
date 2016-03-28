#include <stdlib.h>
#include "Person.h"


/* Complete this header file with include guards and the full declaration for
the int global variable named below. 

Add any additional definitions or declarations needed for the project. 
(See the Project Document for requirements and suggestions.)

Rename this file to "Utility.h" for use in your project. 

Then delete this comment - it is not part of the finished code */


#define MAX_CHAR 64
#define MAX_CHAR_INPUT "%63s"

/* global variable declarations for this module */
extern int g_string_memory;				/* number of bytes used in C-strings */
extern int g_Container_count;			/* number of Ordered_containers currently allocated */
extern int g_Container_items_in_use;	/* number of Ordered_container items currently in use */
extern int g_Container_items_allocated;	/* number of Ordered_container items currently allocated */
extern int g_Meeting_memory;            /* number of meeting struct */


/* Your own decleration and definitions */

void* malloc_with_error_handling(size_t ptr);
int compare_Person_lastname(struct Person *Person1, struct Person *Person2);

