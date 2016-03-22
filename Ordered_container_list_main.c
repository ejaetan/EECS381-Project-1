//
//  main.c
//  Project 1 V2
//
//  Created by Yi Jie Tan on 3/20/16.
//  Copyright © 2016 University of Michigan. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define NDEBUG
#include "Ordered_container.h"
#include "Utility.h"


int main(int argc, const char * argv[]) {
    
    int a = 1, b = 3, c = 5, d = 7,
        e = 2, f = 4, g = 6, h = 8;
    void *ptr1 = &a, *ptr2 = &b, *ptr3 = &c, *ptr4 = &d,
         *ptr5 = &e, *ptr6 = &f, *ptr7 = &g, *ptr8 = &h;
    
    struct Ordered_container* container1 = OC_create_container( (OC_comp_fp_t)compare_int_ptr);
    
    
    assert(container1);
    OC_insert(container1, ptr3);
    print_containter(container1); // 5
    OC_insert(container1, ptr2);
    print_containter(container1); // 3 5
    OC_insert(container1, ptr6);   // 4
    print_containter(container1);  // 3 4 5
    OC_insert(container1, ptr4);
    print_containter(container1); // 3 5 7
    OC_insert(container1, ptr1);
    print_containter(container1); // 1 3 5 7
    OC_insert(container1, ptr8);
    print_containter(container1); // 1 3 5 7 8
    
    printf("%d\n",OC_get_size(container1)); // 5
    printf("%d\n",OC_empty(container1));    // 0
    OC_clear(container1);
    printf("%d\n",OC_get_size(container1));
    
    /*
    OC_insert(container1, ptr3);
    print_containter(container1); // 5
    OC_insert(container1, ptr2);
    print_containter(container1); // 3 5
    OC_insert(container1, ptr4);
    print_containter(container1); // 3 5 7
    OC_insert(container1, ptr1);
    print_containter(container1); // 1 3 5 7
    OC_insert(container1, ptr8);
    print_containter(container1); // 1 3 5 7 8
    
    
    //OC_destroy_container(container1);
    
    void* found_item_ptr1 = OC_find_item(container1, ptr4);
    
    if (!found_item_ptr1) {
        printf("found_item_ptr not found");
    } else {
        printf("found_item_ptr");
        printf(" and it's %d\n", *(int*)OC_get_data_ptr(found_item_ptr1));
    }
    
    OC_delete_item(container1, found_item_ptr1);
    print_containter(container1); // 1 3 5 8

    void* found_item_ptr2 = OC_find_item(container1, ptr1);
    OC_delete_item(container1, found_item_ptr2);
    void* found_item_ptr3 = OC_find_item(container1, ptr8);
    OC_delete_item(container1, found_item_ptr3);
    
    print_containter(container1); // 3 5
    
    OC_insert(container1, ptr6);   // 4
    print_containter(container1);  // 3 4 5
    OC_insert(container1, ptr5);   // 2
    print_containter(container1);  // 2 3 4 5
    printf("%d\n",OC_get_size(container1));

    */

    

    
    
    return 0;
}


