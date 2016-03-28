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
void skip_type_ahead(void);
void add_individual(struct Ordered_container* People);
void print_allocation(const struct Ordered_container* People, const struct Ordered_container* Room);

int main(void) {
    
    char char1, char2;
    
    struct Ordered_container *People = OC_create_container((OC_comp_fp_t) compare_Person_lastname);
    struct Ordered_container *Rooms = OC_create_container((OC_comp_fp_t) compare_Rooms_number);
    
    assert(Rooms);
    assert(People);
    
    while (1) {
        printf("\nEnter command: ");
        
        int var1 = scanf(" %c", &char1);
        int var2 = scanf(" %c", &char2);
        
        assert((var1 == 1)&& (var2 == 1));
        
        switch (char1) {
            case 'p':
                switch (char2) {
                    case 'a':
                        print_allocation(People, Rooms);
                        break;
                        
                    default:
                        break;
                }
                break;
            case 'a':
                switch (char2) {
                    case 'i':
                        add_individual(People);
                        break;
                        
                    default:
                        break;
                }
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
                        return 0;
                        break;
                        
                    default:
                        break;
                }
                break;
            default:
                break;
        }
        skip_type_ahead();
        
    }
    
    
    
    
}


int compare_Rooms_number(int num1, int num2) {
    return num1 - num2;
}

void skip_type_ahead(void) {
    scanf("%*[^\n]");
}
void add_individual(struct Ordered_container* People) {
    const char *firstname[MAX_CHAR], *lastname[MAX_CHAR], *phoneno[MAX_CHAR];
    int scan_input = scanf("%63s %63s %63s", firstname, lastname, phoneno);
    assert(scan_input == 3);
    
    void* find_people_item_ptr = OC_find_item_arg(People, lastname, (OC_find_item_arg_fp_t) get_Person_lastname);
    
    if (find_people_item_ptr) {
        printf("There is already a person with this last name!\n");
    } else {
        struct Person* new_Person = create_Person(firstname, lastname, phoneno);
        OC_insert(People, new_Person);
        printf("Person %s added\n", lastname);
    }
}

void print_allocation(const struct Ordered_container* People, const struct Ordered_container* Room) {
    printf("Memory allocations:\n");
    printf("C-strings: %d bytes total\n", g_string_memory);
    printf("Person structs: %d\n", OC_get_size(People));
    printf("Meeting structs: %d\n", g_Meeting_memory);
    printf("Room structs: %d\n", OC_get_size(Room));
    printf("Containers: %d\n", g_Container_count);
    printf("Container items in use: %d\n", g_Container_items_in_use);
    printf("Container items allocated: %d\n", g_Container_items_allocated);
}


