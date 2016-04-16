//
//  Ordered_container_array_main.c
//  Project 1 V2
//
//  Created by Yi Jie Tan on 4/15/16.
//  Copyright © 2016 University of Michigan. All rights reserved.
//

#include <stdio.h>
#include "Ordered_container.h"

/* Helper function */
void print_container(struct Ordered_container* c_ptr);
int* compare_number(int *data1, int *data2) ;


int main(void)
{
    int num1 = 1, num3 = 3, num5 = 5, num7 = 7;
    int num2 = 2, num4 = 4, num6 = 6, num8 = 8;
    int *no1 = &num1, *no2 = &num2, *no3 = &num3, *no4 = &num4;
    int *no5 = &num5, *no6 = &num6, *no7 = &num7, *no8 = &num8;
    
    struct Ordered_container* container1 = OC_create_container( (OC_comp_fp_t) compare_number);
    OC_insert(container1, no3);
    OC_insert(container1, no1);
    print_container(container1);
    
    return 0;
}




int* compare_number(int *data1, int *data2) {
    return (*data1 - *data2);
}
