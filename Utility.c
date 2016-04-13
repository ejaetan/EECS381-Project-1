 //
//  Utility.c
//  Project 1 V2
//
//  Created by Yi Jie Tan on 3/20/16.
//  Copyright © 2016 University of Michigan. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Utility.h"
#include "Person.h"



/* initialize global variables */
int g_string_memory = 0;
int g_Container_count = 0;
int g_Container_items_in_use = 0;
int g_Container_items_allocated = 0;
int g_Meeting_memory = 0;

void* malloc_with_error_handling(size_t size) {
    
    void* new_ptr = malloc(size);
    
    if (!new_ptr) {
        printf("Allocating for ptr has failed.\nExiting program..\n");
        exit(EXIT_FAILURE);
    }
    
    return new_ptr;
}

void couldnt_open_file_msg(void) {
    printf("Could not open file!\n");
}

void invalid_data_msg(void) {
    printf("Invalid data found in file!\n");
}


