//
//  p1_main.c
//  Project 1 V2
//
//  Created by Yi Jie Tan on 3/27/16.
//  Copyright © 2016 University of Michigan. All rights reserved.
//


#include "Ordered_container.h"
#include "Person.h"
#include "Meeting.h"
#include "Room.h"
#include "Utility.h"
#include <stdio.h>
#include <assert.h>

/* Function Prototype */
int compare_Rooms_number(int num1, int num2);

void add_individual(struct Ordered_container* People);


int main(void) {
    
    char char1, char2;
    
    struct Ordered_container *Rooms = OC_create_container((OC_comp_fp_t) compare_Rooms_number);
    struct Ordered_container *People = OC_create_container((OC_comp_fp_t) compare_Person_lastname);
    
    assert(Rooms);
    assert(People);
    
    printf("\nEnter command: ");
    
    int var1 = scanf(" %c", &char1);
    int var2 = scanf(" %c", &char2);
    
    assert((var1 == 1)&& (var2 == 1));
    
    switch (char1) {
        case 'p':
            switch (char2) {
                case 'i':
                    break;
                    
                default:
                    break;
            }
            break;
        case 'a':
            add_individual(People);
            break;
        case 'r':
            break;
        case 'd':
            break;
        case 's':
            break;
        case 'l':
            break;
        case 'q':
            switch (char2) {
                case 'q':
                    OC_apply(Rooms, (OC_apply_fp_t) destroy_Room);
                    printf("All meetings deleted\n");
                    OC_destroy_container(Rooms);
                    printf("All rooms deleted\n");
                    OC_destroy_container(People);
                    printf("All persons deleted\n");
                    printf("Done\n");
                    break;
                    
                default:
                    break;
            }
            break;
        default:
            break;
    }
    
    
    
    
}


int compare_Rooms_number(int num1, int num2) {
    return num1 - num2;
}

void add_individual(struct Ordered_container* People) {
    
}

