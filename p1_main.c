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
void add_meeting(struct Ordered_container* rooms_ptr);
void add_participant(struct Ordered_container* people_ptr, struct Ordered_container* rooms_ptr);

/* Print functions */
void print_allocation(const struct Ordered_container* people_ptr, const struct Ordered_container* rooms_ptr);
void print_individual(const struct Ordered_container* people_ptr);
void print_room(const struct Ordered_container* rooms_ptr);
void print_meeting(const struct Ordered_container* rooms_ptr);
void print_schedule(const struct Ordered_container* rooms_ptr);
void print_group(const struct Ordered_container* people_ptr);

/* Delete functions */
void delete_individual(struct Ordered_container* people_ptr, struct Ordered_container* rooms_ptr);
void delete_room(struct Ordered_container* rooms_ptr);
void delete_meeting(struct Ordered_container* rooms_ptr);
void delete_participant(struct Ordered_container* people_ptr, struct Ordered_container* rooms_ptr);
void delete_schedule(struct Ordered_container* rooms_ptr);
void delete_group(struct Ordered_container* people_ptr, struct Ordered_container* rooms_ptr);
void delete_all(struct Ordered_container* people_ptr, struct Ordered_container* rooms_ptr);

/* Reschedule functions */
void reschedule_meeting(struct Ordered_container* rooms_ptr);


/* Functions that indicate print message */
void unrecognized_msg(void);
void no_such_lastname_msg(void);
void int_not_read_msg(void);
void no_meeting_msg(void);
void exist_meeting_msg(void);

/* Helper function for individual-related-function */
int compare_Person_lastname_arg(const char* given_lastname_arg, struct Person* Person);

/* Helper function for room-related-function */
int compare_Rooms_num_arg(int *given_num_arg, const struct Room *room);
int scan_room(void);
void* verify_Room(const struct Ordered_container* rooms_ptr);

/* Helper function for meeting-related-function */
int scan_meeting_time(void);
struct Meeting* verify_Meeting(void* found_room_item_ptr);

/* Helper function for lastname-related-function */
void* verify_lastname(const struct Ordered_container* people_ptr);

/* Helper function for delete_individual */
int call_OC_apply_if_arg(const struct Room* room_ptr, struct Person* found_Person);


int main(void) {
    
    char char1, char2;
    
    struct Ordered_container *People = OC_create_container((OC_comp_fp_t) compare_Person_lastname);
    struct Ordered_container *Rooms = OC_create_container((OC_comp_fp_t) compare_Rooms_number);
    
    
    
    while (1) {
        assert(Rooms);
        assert(People);
        
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
                        break;
                    case 'r':
                        print_room(Rooms);
                        break;
                    case 'm':
                        print_meeting(Rooms);
                        break;
                    case 's':
                        print_schedule(Rooms);
                        break;
                    case 'g':
                        print_group(People);
                        break;
                    default:
                        unrecognized_msg();
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
                        break;
                    case 'm':
                        add_meeting(Rooms);
                        break;
                    case 'p':
                        add_participant(People, Rooms);
                        break;
                    default:
                        unrecognized_msg();
                        break;
                }
                break;
            case 'r':
                switch (char2) {
                    case 'm':
                        reschedule_meeting(Rooms);
                        break;
                    default:
                        unrecognized_msg();
                        break;
                }
                break;
            case 'd':
                switch (char2) {
                    case 'i':
                        delete_individual(People, Rooms);
                        break;
                    case 'r':
                        delete_room(Rooms);
                        break;
                    case 'm':
                        delete_meeting(Rooms);
                        break;
                    case 'p':
                        delete_participant(People, Rooms);
                        break;
                    case 's':
                        delete_schedule(Rooms);
                        break;
                    case 'g':
                        delete_group(People, Rooms);
                        break;
                    case 'a':
                        delete_all(People, Rooms);
                        break;
                    default:
                        unrecognized_msg();
                        break;
                }
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
                        unrecognized_msg();
                        break;
                }
                break;
            default:
                unrecognized_msg();
                break;
        }
        
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
    
    void* find_people_item_ptr = OC_find_item_arg(people_ptr, lastname,
                                                  (OC_find_item_arg_fp_t) compare_Person_lastname_arg);
    
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

void add_meeting(struct Ordered_container* rooms_ptr) {
    
    void* found_room_item_ptr = verify_Room(rooms_ptr);
    
    if (!found_room_item_ptr) {
        return;
    }
    
    int meeting_time = scan_meeting_time();
    
    if (meeting_time < 0) {
        return;
    }
    
    struct Meeting* found_meeting_ptr = find_Room_Meeting((struct Room*) OC_get_data_ptr(found_room_item_ptr), meeting_time);

    if (found_meeting_ptr) {
        exist_meeting_msg();
        return;
    } else {
        char topic[MAX_CHAR];
        scanf(INPUT_FORMAT, topic);
        found_meeting_ptr = create_Meeting(meeting_time, topic);
        add_Room_Meeting((struct Room*)OC_get_data_ptr(found_room_item_ptr), found_meeting_ptr);
        printf("Meeting added at %d\n", meeting_time);
    }
}


void add_participant(struct Ordered_container* people_ptr, struct Ordered_container* rooms_ptr) {
    void *found_room_item_ptr = verify_Room(rooms_ptr);
    
    if (!found_room_item_ptr) {
        return;
    }
    
    struct Meeting* found_meeting_ptr = verify_Meeting(found_room_item_ptr);
    
    if (!found_meeting_ptr) {
        return;
    }
    
    void *found_lastname_item_ptr = verify_lastname(people_ptr);
    
    if (!found_lastname_item_ptr) {
        return;
    }
    
    struct Person *found_Person = (struct Person*) OC_get_data_ptr(found_lastname_item_ptr);
    
    if (!(is_Meeting_participant_present(found_meeting_ptr, found_Person))) {
        printf("This person is already a participant!\n");
        return;
    }
    
    int add_participant = add_Meeting_participant(found_meeting_ptr, found_Person);
    
    if (add_participant) {
        printf("Participant %s added\n", get_Person_lastname(found_Person));
    }
    
    
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

void print_individual(const struct Ordered_container* people_ptr) {
 
    void *found_lastname_item_ptr = verify_lastname(people_ptr);
    
    if (!found_lastname_item_ptr) {
        return;
    }
    
    struct Person* found_Person = OC_get_data_ptr(found_lastname_item_ptr);
    print_Person(found_Person);

}

void print_room(const struct Ordered_container* rooms_ptr) {
    void* found_room_item_ptr = verify_Room(rooms_ptr);
    
    if (found_room_item_ptr) {
        print_Room(OC_get_data_ptr(found_room_item_ptr));
    }
}


void print_meeting(const struct Ordered_container* rooms_ptr) {
    void* found_room_item_ptr = verify_Room(rooms_ptr);
    
    if (!found_room_item_ptr) {
        return;
    }
    
    struct Meeting* found_meeting_ptr = verify_Meeting(found_room_item_ptr);
    
    if (!found_meeting_ptr) {
        return;
    }
    
    print_Meeting(found_meeting_ptr);
}

void print_schedule(const struct Ordered_container* rooms_ptr) {
    int OC_size = OC_get_size(rooms_ptr);
    
    if (!OC_size) {
        printf("List of rooms is empty\n");
        return;
    }
    
    if (OC_size > 0) {
        printf("Information for %d rooms:\n", OC_size);
        OC_apply(rooms_ptr, (OC_apply_fp_t) print_Room);
    }
    
}

void print_group(const struct Ordered_container* people_ptr) {
    int OC_size = OC_get_size(people_ptr);
    
    if (!OC_size) {
        printf("List of people is empty\n");
        return;
    }
    
    if (OC_size > 0) {
        printf("Information for %d people:\n", OC_size);
        OC_apply(people_ptr, (OC_apply_fp_t) print_Person);
    }
    
}

/* Delete functions */
void delete_individual(struct Ordered_container* people_ptr, struct Ordered_container* rooms_ptr) {
    void *found_lastname_item_ptr = verify_lastname(people_ptr);
    
    if (!found_lastname_item_ptr) {
        return;
    }
    
    struct Person *found_Person = OC_get_data_ptr(found_lastname_item_ptr);
    int apply_result = OC_apply_if_arg(rooms_ptr, (OC_apply_if_arg_fp_t) call_OC_apply_if_arg, found_Person);
    
    if (apply_result) {
        printf("This person is a participant in a meeting!\n");
        skip_type_ahead();
        return;
    }
    
    OC_delete_item(people_ptr, found_lastname_item_ptr);
    printf("Person %s deleted\n", get_Person_lastname(found_Person));
}

void delete_room(struct Ordered_container* rooms_ptr) {
    void* found_room_item_ptr = verify_Room(rooms_ptr);
    
    if (!found_room_item_ptr) {
        return;
    }
    
    struct Room* found_Room = OC_get_data_ptr(found_room_item_ptr);
    int Room_number = get_Room_number(found_Room);
    destroy_Room(found_Room);
    OC_delete_item(rooms_ptr, found_room_item_ptr);
    printf("Room %d deleted\n", Room_number);
}

void delete_meeting(struct Ordered_container* rooms_ptr) {
    void* found_room_item_ptr = verify_Room(rooms_ptr);
    
    if (!found_room_item_ptr) {
        return;
    }
    
    struct Meeting* found_meeting_ptr = verify_Meeting(found_room_item_ptr);
    int meeting_time = get_Meeting_time(found_meeting_ptr);
    
    if (!found_meeting_ptr) {
        return;
    }
    
    destroy_Meeting(found_meeting_ptr);
    remove_Room_Meeting(OC_get_data_ptr(found_room_item_ptr), found_meeting_ptr);
    
    printf("Meeting at %d deleted\n", meeting_time);
}

void delete_participant(struct Ordered_container* people_ptr, struct Ordered_container* rooms_ptr) {
    void *found_room_item_ptr = verify_Room(rooms_ptr);
    
    if (!found_room_item_ptr) {
        return;
    }
    
    struct Meeting* found_meeting_ptr = verify_Meeting(found_room_item_ptr);
    
    if (!found_meeting_ptr) {
        return;
    }
    
    void *found_lastname_item_ptr = verify_lastname(people_ptr);
    
    if (!found_lastname_item_ptr) {
        return;
    }
    
    struct Person *found_Person = (struct Person*) OC_get_data_ptr(found_lastname_item_ptr);
    
    if (is_Meeting_participant_present(found_meeting_ptr, found_Person)) {
        printf("This person is not a participant in the meeting!\n");
        skip_type_ahead();
        return;
    }
    
    remove_Meeting_participant(found_meeting_ptr, found_Person);
    printf("Participant %s deleted\n", get_Person_lastname(found_Person));
}

void delete_schedule(struct Ordered_container* rooms_ptr) {
    OC_apply(rooms_ptr, (OC_apply_fp_t) clear_Room);
    printf("All meetings deleted\n");
    
}

void delete_group(struct Ordered_container* people_ptr, struct Ordered_container* rooms_ptr) {
    if (g_Meeting_memory) {
        printf("Cannot clear people list unless there are no meetings!\n");
        return;
    }
    
    OC_apply(people_ptr, (OC_apply_fp_t) destroy_Person);
    OC_clear(people_ptr);
    printf("All persons deleted\n");
}

void delete_all(struct Ordered_container* people_ptr, struct Ordered_container* rooms_ptr) {
    OC_apply(rooms_ptr, (OC_apply_fp_t) destroy_Room);
    printf("All meetings deleted\n");
    OC_clear(rooms_ptr);
    printf("All rooms deleted\n");
    delete_group(people_ptr, rooms_ptr);
    
}

/* Reschedule functions */
void reschedule_meeting(struct Ordered_container* rooms_ptr) {
    void* found_old_room_item_ptr = verify_Room(rooms_ptr);
    
    if (!found_old_room_item_ptr) {
        return;
    }
    
    struct Meeting* found_old_meeting_ptr = verify_Meeting(found_old_room_item_ptr);
    
    if (!found_old_meeting_ptr) {
        return;
    }
    
    void* found_new_room_item_ptr = verify_Room(rooms_ptr);
    
    if (!found_new_room_item_ptr) {
        return;
    }
    
    struct Meeting* found_new_meeting_ptr = NULL;
    int new_meeting_time = scan_meeting_time();
    
    if (new_meeting_time < 0) {
        return;
    }
    
    found_new_meeting_ptr = find_Room_Meeting((struct Room*) OC_get_data_ptr(found_new_room_item_ptr), new_meeting_time);
    
    
    if (found_new_meeting_ptr) {
        exist_meeting_msg();
        return;
    }

    struct Meeting* reschedule_meeting = found_old_meeting_ptr;
    int remove_Meeting_result = remove_Room_Meeting(OC_get_data_ptr(found_old_room_item_ptr), found_old_meeting_ptr);
    assert(!remove_Meeting_result);
    
    set_Meeting_time(reschedule_meeting, new_meeting_time);
    int add_Meeting_result = add_Room_Meeting(OC_get_data_ptr(found_new_room_item_ptr), reschedule_meeting);
    assert(!add_Meeting_result);
    
    printf("Meeting rescheduled to room %d at %d\n", get_Room_number(OC_get_data_ptr(found_new_room_item_ptr)), new_meeting_time);
}


/* Functions that indicate print message */
void unrecognized_msg(void) {
    printf("Unrecognized command!\n");
    skip_type_ahead();
}

void no_such_lastname_msg(void) {
    printf("No person with that name!\n");
    skip_type_ahead();
}

void int_not_read_msg(void) {
    printf("Could not read an integer value!\n");
    skip_type_ahead();
}

void no_meeting_msg(void) {
    printf("No meeting at that time!\n");
    skip_type_ahead();
}

void exist_meeting_msg(void) {
    printf("There is already a meeting at that time!\n");
    skip_type_ahead();
}

/* Helper function for individual-related-function */
int compare_Person_lastname_arg(const char *given_lastname_arg,
                                struct Person* Person) {
    return strcmp(given_lastname_arg, get_Person_lastname(Person));
    
}

/* Helper function for room-related-function */
int compare_Rooms_num_arg(int* given_num_arg, const struct Room *room) {
    return (*(int*)given_num_arg )- get_Room_number(room);
}

int scan_room(void) {
    int room_num = -1;
    int scan_input = scanf("%d",&room_num);
    
    if (scan_input != 1) {
        int_not_read_msg();
        return room_num;
    }
    if (room_num < 1) {
        printf("Room number is not in range!\n");
        skip_type_ahead();
    }
    return room_num;
}

void* verify_Room(const struct Ordered_container* rooms_ptr) {
    
    int scan_room_num = scan_room();
    
    if (scan_room_num <= 0) {
        return NULL;
    }
    
    void *find_room_item_ptr = OC_find_item_arg(rooms_ptr, &scan_room_num,
                                                (OC_find_item_arg_fp_t) compare_Rooms_num_arg);
    
    if (!find_room_item_ptr) {
        printf("No room with that number!\n");
        skip_type_ahead();
    }
    
    return find_room_item_ptr;
}

/* Helper function for meeting-related-function */
int scan_meeting_time(void) {
    
    int meeting_time = 0;
    int scan_input = scanf("%d", &meeting_time);
    
    if (scan_input != 1) {
        int_not_read_msg();
        return -1;
    }
    
    if ((time_conversion(meeting_time) < 9) || (time_conversion(meeting_time) > 17)) {
        printf("Time is not in range!\n");
        skip_type_ahead();
        return -1;
    }
    
    return meeting_time;
}

struct Meeting*  verify_Meeting(void* found_room_item_ptr) {
    struct Meeting* found_meeting_ptr = NULL;
    int meeting_time = scan_meeting_time();
    
    if (meeting_time < 0) {
        return found_meeting_ptr;
    }
    
    found_meeting_ptr = find_Room_Meeting((struct Room*) OC_get_data_ptr(found_room_item_ptr), meeting_time);
    
    if (!found_meeting_ptr) {
        no_meeting_msg();
    }
    
    return found_meeting_ptr;

}

/* Helper function for lastname-related-function */
void* verify_lastname(const struct Ordered_container* people_ptr) {
    char lastname[MAX_CHAR];
    int scan_lastname = scanf(INPUT_FORMAT, lastname);
    assert(scan_lastname == 1);
    
    void* find_people_item_ptr = OC_find_item_arg(people_ptr, lastname,
                                                  (OC_find_item_arg_fp_t) compare_Person_lastname_arg);
    if (!find_people_item_ptr) {
        no_such_lastname_msg();
        skip_type_ahead();
    }
    
    return  find_people_item_ptr;
}


/* Helper function for delete function */
int call_OC_apply_if_arg(const struct Room* room_ptr, struct Person* found_Person) {
    return OC_apply_if_arg(get_Room_Meetings(room_ptr), (OC_apply_if_arg_fp_t) is_Meeting_participant_present, found_Person);
}
