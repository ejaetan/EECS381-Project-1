#include "Room.h"
#include "Ordered_container.h"
#include "Utility.h"
#include "Meeting.h"
#include <assert.h>

/* Helper functions */
int time_conversion(int time);
int compare_Meeting_time(struct Meeting* meeting_ptr1, struct Meeting* meeting_ptr2);
int compare_Meeting_time_arg(int *given_time, const struct Meeting* meeting_ptr);

/* a Room contains a container of meetings and a room number */
struct Room {
	struct Ordered_container* meetings;	/* a container of pointers to Meeting objects */
	int number;
};

struct Room* create_Room(int number) {
    struct Room *new_Room = (struct Room*)malloc_with_error_handling(sizeof(struct Room));
    new_Room->meetings = OC_create_container((OC_comp_fp_t) compare_Meeting_time);
    new_Room->number = number;

    return new_Room;
    
}

/* Destroy a Room object.
 This is the only function that frees the memory for a Room
 and the contained data. The Meetings are destroyed before the
 Meeting list is emptied. */
void destroy_Room(struct Room* room_ptr) {
    assert(room_ptr);

    OC_apply(room_ptr->meetings, (OC_apply_fp_t) destroy_Meeting);
    OC_destroy_container(room_ptr->meetings);
    free(room_ptr);
    room_ptr = NULL;
}

int get_Room_number(const struct Room* room_ptr) {
    assert(room_ptr);
    return room_ptr->number;
}

int add_Room_Meeting(struct Room* room_ptr, const struct Meeting* meeting_ptr) {
    assert(room_ptr);
    
    if (OC_find_item(room_ptr->meetings, (void*) meeting_ptr)) {
        return -1;
    } else {
        OC_insert(room_ptr->meetings, (void*) meeting_ptr);
        return 0;
    }
}

struct Meeting* find_Room_Meeting(const struct Room* room_ptr, int time) {
    assert(room_ptr);
    
    void* find_meeting_item_ptr = OC_find_item_arg(room_ptr->meetings, &time, (OC_find_item_arg_fp_t) compare_Meeting_time_arg);
    
    return  find_meeting_item_ptr ? (struct Meeting*) OC_get_data_ptr(find_meeting_item_ptr): NULL;
}

int remove_Room_Meeting(struct Room* room_ptr, const struct Meeting* meeting_ptr) {
    assert(room_ptr);
    
    void* find_meeting_item_ptr = OC_find_item(room_ptr->meetings, (void*) meeting_ptr);
    if (find_meeting_item_ptr) {
        OC_delete_item(room_ptr->meetings, find_meeting_item_ptr);
        return 0;
    } else {
        return -1;
    }
    
}

void clear_Room(struct Room* room_ptr) {
    assert(room_ptr);
    OC_apply(room_ptr->meetings, (OC_apply_fp_t) destroy_Meeting);
    OC_clear(room_ptr->meetings);
}

const struct Ordered_container* get_Room_Meetings(const struct Room* room_ptr) {
    assert(room_ptr);
    const struct Ordered_container* Meeting_OC = room_ptr->meetings;
    return Meeting_OC;
}


void print_Room(const struct Room* room_ptr) {
    assert(room_ptr);
    printf("--- Room %d ---\n", room_ptr->number);
    
    if (OC_get_size(room_ptr->meetings) > 0) {
        OC_apply(room_ptr->meetings, (OC_apply_fp_t) print_Meeting);
    } else {
        printf("No meetings are scheduled\n");
    }
}

/* Write the room data to a file. */
void save_Room(const struct Room* room_ptr, FILE* outfile) {
    if (outfile) {
        fprintf(outfile, "%d %d\n", get_Room_number(room_ptr), OC_get_size(room_ptr->meetings));
        OC_apply_arg(room_ptr->meetings, (OC_apply_arg_fp_t) save_Meeting, outfile);
    } else {
        couldnt_open_file_msg();
    }
}

/* Read a room's data from a file stream, create the data object and
 return a pointer to it, NULL if invalid data discovered in file.
 No check made for whether the room already exists or not. */
struct Room* load_Room(FILE* infile, const struct Ordered_container* people) {
    if (!infile) {
        couldnt_open_file_msg();
        return NULL;
    }
    
    struct Room* new_Room = NULL;
    int total_meeting = 0, room_number = 0;
    
    int scan_result = fscanf(infile, "%d %d\n", &room_number, &total_meeting);
    if (scan_result != 2) {
        invalid_data_msg();
        return NULL;
    }
    assert(room_number && total_meeting);
    
    new_Room = create_Room(room_number);
    
    for (; total_meeting > 0; total_meeting--) {
        struct Meeting* new_Meeting = load_Meeting(infile, people);
        add_Room_Meeting(new_Room, new_Meeting);
    }
    
    return new_Room;
    
}


/* Helper functions */
int time_conversion(int time) {
    if ( (time < 5) && (time > 0) ) {
        return time += 12;
    }
    return  time;
}

int compare_Meeting_time(struct Meeting* meeting_ptr1,
                         struct Meeting* meeting_ptr2) {
    return (time_conversion(get_Meeting_time(meeting_ptr1)) -
            time_conversion(get_Meeting_time(meeting_ptr2)));
}

int compare_Meeting_time_arg(int *given_time, const struct Meeting* meeting_ptr) {
    return time_conversion(*(int*)given_time) -
           time_conversion(get_Meeting_time(meeting_ptr));
}

