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
#include <string.h>

/* Functions Prototype */
int compare_Rooms_number(int num1, int num2);
void skip_type_ahead(void);

/* Add functions */
void add_individual(struct Ordered_container* people_ptr);
void add_room(struct Ordered_container* rooms_ptr);

/* Print functions */
void print_allocation(const struct Ordered_container* people_ptr, const struct Ordered_container* rooms_ptr);
void print_individual(const struct Ordered_container* people_ptr);

/* Helper function for individual-related-function */
int compare_Person_lastname_arg(const char* given_lastname_arg, struct Person* Person);

int compare_Rooms_num_arg(int *given_num_arg, const struct Room *room);
int scan_room(void);

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
                    case 'i':
                        print_individual(People);
                    default:
                        break;
                }
                break;
            case 'a':
                switch (char2) {
                    case 'i':
                        add_individual(People);
                        break;
                    case 'r':
                        add_room(Rooms);
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

/* Add funtions */
void add_individual(struct Ordered_container* people_ptr) {
    const char firstname[MAX_CHAR], lastname[MAX_CHAR], phoneno[MAX_CHAR];
    
    int scan_input = scanf("%63s %63s %63s", firstname, lastname, phoneno);
    assert(scan_input == 3);
    
    void* find_people_item_ptr = OC_find_item_arg(people_ptr, lastname, (OC_find_item_arg_fp_t) compare_Person_lastname_arg);
    
    if (find_people_item_ptr) {
        printf("There is already a person with this last name!\n");
        skip_type_ahead();
    } else {
        struct Person* new_Person = create_Person(firstname, lastname, phoneno);
        OC_insert(people_ptr, new_Person);
        printf("Person %s added\n", lastname);
    }
}

void add_room(struct Ordered_container* rooms_ptr) {
    int scan_room_num = scan_room();
    
    if (scan_room_num <= 0) {
        return;
    }
    
    void *find_room_item_ptr = OC_find_item_arg(rooms_ptr, &scan_room_num,
                                                (OC_find_item_arg_fp_t) compare_Rooms_num_arg);
    
    if (find_room_item_ptr) {
        printf("There is already a room with this number!\n");
        skip_type_ahead();
    } else {
        struct Room *new_Room = create_Room(scan_room_num);
        OC_insert(rooms_ptr, new_Room);
        printf("Room %d added\n", scan_room_num);
    }
    
    
    
}

int compare_Rooms_num_arg(int* given_num_arg, const struct Room *room) {
    return (*(int*)given_num_arg )- get_Room_number(room);
}

int scan_room(void) {
    int room_num = 0;
    int scan_input = scanf("%d",&room_num);
    
    if (scan_input != 1) {
        printf("Could not read an integer value!\n");
        skip_type_ahead();
    } else if (room_num < 1) {
        printf("Room number is not in range!\n");
        skip_type_ahead();
    }
    
    return room_num;
    
    
}

/* print functions */
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

void print_individual(const struct Ordered_container* People) {
    const char lastname[MAX_CHAR];
    
    int scan_input = scanf(INPUT_FORMAT, lastname);
    assert(scan_input == 1);
    
    void* find_people_item_ptr = OC_find_item_arg(People, lastname, (OC_find_item_arg_fp_t) compare_Person_lastname_arg);
    
    if (find_people_item_ptr) {
        struct Person* found_person = OC_get_data_ptr(find_people_item_ptr);
        print_Person(found_person);
    } else {
        printf("No person with that name!\n");
    }
}


int compare_Person_lastname_arg(const char *given_lastname_arg,
                                struct Person* Person) {
    return strcmp(given_lastname_arg, get_Person_lastname(Person));
    
}


