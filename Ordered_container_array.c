#include "Ordered_container.h"
#include "Utility.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/* Helper function */
void print_container(struct Ordered_container* c_ptr);
void grow_array(struct Ordered_container* c_ptr);

/* A complete type declaration for Ordered_container implemented as an array */
struct Ordered_container {
	OC_comp_fp_t comp_fun;	/* pointer to comparison function  */
	void** array;			/* pointer to array of pointers to void */
	int allocation;			/* current size of array */
	int size;				/* number of items currently in the array */
};

struct Ordered_container* OC_create_container(OC_comp_fp_t f_ptr) {
    struct Ordered_container* new_Container = (struct Ordered_container*)(malloc_with_error_handling(sizeof(struct Ordered_container)));

    
    new_Container->comp_fun = f_ptr;
    new_Container->allocation = 3;
    new_Container->array = (void**) malloc_with_error_handling((new_Container->allocation) * sizeof(void*));;
    new_Container->size = 0;

    g_Container_items_allocated += 3;
    g_Container_count++;
    return new_Container;
}


void OC_destroy_container(struct Ordered_container* c_ptr) {
    if (c_ptr) {
        
        int total_memory_allocated = c_ptr->allocation;
        int total_items_in_use = c_ptr->size;

        for(int i = 0; i < total_memory_allocated; i++) {
            free(c_ptr->array[i]);
            g_Container_items_allocated--;
        }
        
        
        free(c_ptr);
        c_ptr = NULL;
        
        g_Container_items_in_use -= total_items_in_use;
        g_Container_count--;
    }
    
}

/* Delete all the items in the container and initialize it.
 Caller is responsible for deleting any pointed-to data first. */
void OC_clear(struct Ordered_container* c_ptr) {
    if (c_ptr) {
        int total_memory_allocated = c_ptr->allocation;
        int total_items_in_use = c_ptr->size;
        
        for(int i = 0; i < total_memory_allocated; i++) {
            free(c_ptr->array[i]);
            g_Container_items_allocated--;
        }
        
        c_ptr->allocation = 3;
        c_ptr->array = (void**) malloc_with_error_handling((c_ptr->allocation) * sizeof(void*));;
        c_ptr->size = 0;
        
        g_Container_items_in_use -= total_items_in_use;
        g_Container_items_allocated += 3;
    }
}

/* Return the number of items currently stored in the container */
int OC_get_size(const struct Ordered_container* c_ptr) {
    return c_ptr->size;
}

/* Return non-zero (true) if the container is empty, zero (false) if the container is non-empty */
int OC_empty(const struct Ordered_container* c_ptr) {
    return (c_ptr->size) ? 0 : 1;
}

/*
 Functions for working with individual items in the container.
 */

/* Get the data object pointer from an item. */
void* OC_get_data_ptr(const void* item_ptr) {
    return (*(void**) item_ptr);
}

/* Delete the specified item.
 Caller is responsible for any deletion of the data pointed to by the item. */
void OC_delete_item(struct Ordered_container* c_ptr, void* item_ptr) {

}

/*
 Functions that search and insert into the container using the supplied comparison function.
 */

/* Helper function: Binary search function that determine the location of the item requested by OC_find function */
int binary_search(const struct Ordered_container* c_ptr, const void* data_ptr,
                   OC_comp_fp_t comp_func, int *found_index);
int binary_search(const struct Ordered_container* c_ptr, const void* data_ptr,
                   OC_comp_fp_t comp_func, int *found_index) {
    
    int low, high, mid, num = -1;
    *found_index = num;
    
    low = 0;
    high = (c_ptr->size) - 1;
    
    while (low <= high) {
        mid = ((low + high) / 2);
        if ( comp_func(data_ptr, c_ptr->array[mid])  < 0 ) {
            high = mid - 1;
        } else if ( comp_func(data_ptr, c_ptr->array[mid])  > 0 ) {
            low = mid + 1;
        } else if ( comp_func(data_ptr, c_ptr->array[mid])  == 0 ) {
            *found_index = mid;
            return 0;
        }
    }

    if (*found_index < 0) {
        high++;
        *found_index = high;
    }
    
    return 1;

}


void OC_insert(struct Ordered_container* c_ptr, void* data_ptr) {
    assert(c_ptr);

    int i = 0, search_result = -1, found_index = -1;
    int original_array_size = c_ptr->allocation;
    int total_items_in_original_array = c_ptr->size;
    
    search_result = binary_search(c_ptr, data_ptr, c_ptr->comp_fun, &found_index);
    
    if (original_array_size == total_items_in_original_array) {
        grow_array(c_ptr);
    }
    
    for (i = total_items_in_original_array; i > found_index; i--) {
        c_ptr->array[i] = c_ptr->array[i - 1];
    }
    
    c_ptr->array[i] = data_ptr;
    
    
    g_Container_items_in_use++;
    c_ptr->size++;

}


void grow_array(struct Ordered_container* c_ptr) {
    int copy_array_size = 2 * (c_ptr->allocation + 1);
    void** copy_array =  (void**) malloc_with_error_handling(copy_array_size * sizeof(void*));
    
    for (int i = 0; i < c_ptr->size; i++) {
        copy_array[i] = c_ptr->array[i];
    }
    
    free(c_ptr->array);
    c_ptr->array = copy_array;

}

void* OC_find_item(const struct Ordered_container* c_ptr, const void* data_ptr) {
    int array_index = 0;
    int search_result = binary_search(c_ptr, data_ptr, c_ptr->comp_fun , &array_index);
    
    return (search_result == 0) ? c_ptr->array[array_index] : NULL;
}

void* OC_find_item_arg(const struct Ordered_container* c_ptr, const void* arg_ptr, OC_find_item_arg_fp_t fafp) {
    
    int array_index = 0;
    int search_result = binary_search(c_ptr, arg_ptr, fafp , &array_index);
    
    return (search_result == 0) ? c_ptr->array[array_index] : NULL;
}


void OC_apply(const struct Ordered_container* c_ptr, OC_apply_fp_t afp) {
    for (int i = 0; i < c_ptr->size; i++) {
        afp(*(void**)(c_ptr->array[i]));
    }
}


int OC_apply_if(const struct Ordered_container* c_ptr, OC_apply_if_fp_t afp) {
    int result = -1;
    
    for (int i = 0; (i < c_ptr->size) &&
         (result = afp(*(void**)(c_ptr->array[i]))) == 0 ; i++) {
        ;
    }
    
    return result;
}

void OC_apply_arg(const struct Ordered_container* c_ptr, OC_apply_arg_fp_t afp,
                  void* arg_ptr) {
    
    int i = 0;
    while (i < c_ptr->size) {
        afp(*(void**) (c_ptr->array[i]), arg_ptr);
        i++;
    }

}

int OC_apply_if_arg(const struct Ordered_container* c_ptr, OC_apply_if_arg_fp_t afp, void* arg_ptr) {
    int result = -1;
    
    for (int i = 0; (i < c_ptr->size) &&
         (result = afp(*(void**)(c_ptr->array[i]), arg_ptr)) == 0 ; i++) {
        ;
    }
    return result;
}

/* Helper function */
void print_container(struct Ordered_container* c_ptr) {
    for (int i = 0; i < c_ptr->size; i++) {
        printf("%d\t", *(int*)(c_ptr->array[i]));
    }
    printf("\n");
}

