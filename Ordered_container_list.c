#include "Ordered_container.h"
#include "Utility.h"
#include <stdlib.h>
#include <stdio.h>



/* struct LL_Node structure declaration. This declaration is local to this file. 
This is a two-way or doubly-linked list. Each node has a pointer to the previous 
node and another pointer to the next node in the list. This means insertions or
removals of a node can be made in constant time, once the location has been
determined. */
struct LL_Node { 
    struct LL_Node* prev;      /* pointer to the previous node */
	struct LL_Node* next;		/* pointer to the next node */
	void* data_ptr; 			/* uncommitted pointer to the data item */
};

/* Helper function's prototype */
int equals_or_justOver(const struct Ordered_container* c_ptr, void* data_ptr, OC_comp_fp_t comp_func, struct LL_Node ** current_node);


/* Declaration for Ordered_container. This declaration is local to this file.  
A pointer is maintained to the last node in the list as well as the first, 
meaning that additions to the end of the list can be made in constant time. 
The number of nodes in the list is kept up-to-date in the size member
variable, so that the size of the list can be accessed in constant time. */
struct Ordered_container {
	OC_comp_fp_t comp_func;
	struct LL_Node* first;
	struct LL_Node* last;
	int size;
};

/*
 Functions for the entire container.
 */

struct Ordered_container* OC_create_container(OC_comp_fp_t f_ptr) {
    struct Ordered_container* new_Container = (struct Ordered_container*)(malloc_with_error_handling(sizeof(struct Ordered_container)));
    
    new_Container->comp_func = f_ptr;
    new_Container->first = NULL;
    new_Container->last = NULL;
    new_Container->size = 0;
    g_Container_count++;
    
    return new_Container;
}

void OC_destroy_container(struct Ordered_container* c_ptr) {
    if (c_ptr) {
        OC_clear(c_ptr);
        free(c_ptr);
        c_ptr = NULL;
        
        g_Container_count--;
    }
}

void OC_clear(struct Ordered_container* c_ptr) {
    
    if (c_ptr) {
        struct LL_Node* delete_node = c_ptr->first;
        
        while (delete_node) {
            struct  LL_Node* next_delete_node = delete_node->next;
            free(delete_node);
            delete_node = NULL;
            delete_node = next_delete_node;
            
            c_ptr->size--;
            g_Container_items_in_use--;
            g_Container_items_allocated--;
        }
        c_ptr->first = c_ptr->last = NULL;
    }
}

int OC_get_size(const struct Ordered_container* c_ptr) {
    return c_ptr->size;
}

int OC_empty(const struct Ordered_container* c_ptr) {
    return (!(c_ptr->size)) ? -1 : 0;
}


/*
 Functions for working with individual items in the container.
 */

void* OC_get_data_ptr(const void* item_ptr) {
    return ( (struct LL_Node*)item_ptr )->data_ptr;
}

void OC_delete_item(struct Ordered_container* c_ptr, void* item_ptr) {
    if (c_ptr) {
        struct LL_Node *current_node, *current_node_prev, *current_node_next;
        current_node = item_ptr;
        
        if (OC_get_size(c_ptr) > 1) {
            
            // delete item is the first one of the list
            if (!current_node->prev) {
                c_ptr->first = current_node->next;
                c_ptr->first->prev = NULL;
             
            // delete item is in the middle of the list
            } else if ( (current_node->prev) && (current_node->next)) {
                current_node_prev = current_node->prev;
                current_node_next = current_node->next;
                current_node_prev->next = current_node_next;
                current_node_next->prev = current_node_prev;
                
            // delete item is the last one of the list
            } else if (!current_node->next) {
                c_ptr->last = current_node->prev;
                c_ptr->last->next = NULL;
            }
        }
        
        free(current_node);
        current_node = NULL;
        
        c_ptr->size--;
        g_Container_items_in_use--;
        g_Container_items_allocated--;
        
    }
}


/*
 Functions that search and insert into the container using the supplied comparison function.
 */

int equals_or_justOver(const struct Ordered_container* c_ptr, void* data_ptr, OC_comp_fp_t comp_func, struct LL_Node ** current_node) {
    
    int result = -1;
    *current_node = c_ptr->first;
    
    while ( (*current_node) &&
           ((result = comp_func(data_ptr, (*current_node)->data_ptr)) > 0) ) {
        *current_node = (*current_node)->next;
    }
    
    return result;
}

void OC_insert(struct Ordered_container* c_ptr, void* data_ptr) {
    if ( c_ptr ) {
        int OC_size = OC_get_size(c_ptr);
        struct LL_Node* new_node = malloc_with_error_handling(sizeof(struct LL_Node));
        new_node->data_ptr = data_ptr;
        
        if ( OC_size == 0 ) {
            c_ptr->first = c_ptr->last = new_node;
            c_ptr->first->prev = c_ptr->last->next = NULL;
        } else {
            struct LL_Node *current_node = NULL;
            equals_or_justOver(c_ptr, data_ptr, c_ptr->comp_func,
                               &current_node);
            if (!current_node) {
                // insert new item as the last item of the list
                struct LL_Node* new_node_prev = c_ptr->last;
                new_node_prev->next = new_node;
                new_node->prev = new_node_prev;
                new_node->next = NULL;
                c_ptr->last = new_node;
            
            } else {
                // insert new item as the first item of the list
                if (!current_node->prev) {
                    current_node->prev = new_node;
                    new_node->next = current_node;
                    new_node->prev = NULL;
                    c_ptr->first = new_node;
                
                // insert new item in the middle item of the list
                } else {
                    struct LL_Node* new_node_prev = current_node->prev;
                    current_node->prev = new_node;
                    new_node->next = current_node;
                    new_node->prev = new_node_prev;
                    new_node_prev->next = new_node;
                }
            }
        }

        
        g_Container_items_allocated++;
        g_Container_items_in_use++;
        c_ptr->size++;
        
    }
}


void* OC_find_item(const struct Ordered_container* c_ptr, const void* data_ptr) {
    
    int found_result = -1;
    struct LL_Node* current_node = NULL;
    
    if (c_ptr) {
        found_result = equals_or_justOver(c_ptr, (void*) data_ptr,
                                          c_ptr->comp_func, &current_node);
    }
    return (found_result == 0) ? (void*) current_node : NULL;
}

void* OC_find_item_arg(const struct Ordered_container* c_ptr, const void* arg_ptr, OC_find_item_arg_fp_t fafp) {
    
    int found_result = -1;
    struct LL_Node* current_node = NULL;
    
    if (c_ptr) {
        found_result = equals_or_justOver(c_ptr, (void*) arg_ptr,
                                          fafp, &current_node);
    }
    
    return (found_result == 0) ? (void*) current_node : NULL;
}

void OC_apply(const struct Ordered_container* c_ptr, OC_apply_fp_t afp) {
    if (c_ptr) {
        struct LL_Node *current_node = c_ptr->first;
        while (current_node) {
            afp(current_node->data_ptr);
            current_node = current_node->next;
        }
    }
}

int OC_apply_if(const struct Ordered_container* c_ptr, OC_apply_if_fp_t afp) {
    int result = -1;
    
    if (c_ptr) {
        struct LL_Node *current_node = c_ptr->first;
        
        while ( (current_node) &&
               ((result = afp(current_node->data_ptr)) == 0)) {
            current_node = current_node->next;
        }
    }
    return result;
}

void OC_apply_arg(const struct Ordered_container* c_ptr,
                  OC_apply_arg_fp_t afp, void* arg_ptr) {
    if (c_ptr) {
        struct LL_Node *current_node = c_ptr->first;
        while (current_node) {
            afp(current_node->data_ptr, arg_ptr);
            current_node = current_node->next;
        }
    }
}

int OC_apply_if_arg(const struct Ordered_container* c_ptr, OC_apply_if_arg_fp_t afp, void* arg_ptr) {
    int result = -1;
    
    if (c_ptr) {
        struct LL_Node *current_node = c_ptr->first;
        
        while ( (current_node) &&
               ((result = afp(current_node->data_ptr, arg_ptr)) == 0)) {
            current_node = current_node->next;
        }
    }
    return result;
    
}

/* Helper function */
void print_containter(struct Ordered_container* c_ptr);

void print_containter(struct Ordered_container* c_ptr) {
    struct LL_Node *current_node = c_ptr->first;
    
    while (current_node) {
        printf("%d\t", *(int*) (current_node->data_ptr) );
        current_node = current_node->next;
    }
    printf("\n");
    
}













