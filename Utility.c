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


void skip_type_ahead(void) {
    scanf("%*[^\n]");
}

void* malloc_with_error_handling(size_t size) {
    
    void* new_ptr = malloc(size);
    
    if (!new_ptr) {
        printf("Allocating for ptr has failed.\nExiting program..\n");
        exit(EXIT_FAILURE);
    }
    
    return new_ptr;
}


int compare_Person_lastname(struct Person *Person1, struct Person *Person2) {
    return strcmp(get_Person_lastname(Person1), get_Person_lastname(Person2));
    
}
 

int time_conversion(int time) {
    if ( (time < 5) && (time > 0) ) {
        return time += 12;
    }
    return  time;
}

void couldnt_open_file_msg(void) {
    printf("Could not open file!\n");
    skip_type_ahead();
}

void invalid_data_msg(void) {
    printf("Invalid data found in file!\n");
    skip_type_ahead();
}


