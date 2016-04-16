#include "Meeting.h"
#include "Utility.h"
#include "Ordered_container.h"
#include "Person.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
/* a Meeting contains a time, a topic, and a container of participants */
struct Meeting {
	char* topic;
	int time;
	struct Ordered_container* participants;	/* a container of pointers to struct Person objects */
};

struct Meeting* create_Meeting(int time, const char* topic) {
    struct Meeting* new_Meeting = (struct Meeting*) malloc_with_error_handling(sizeof(struct Meeting));
    
    if (new_Meeting) {
        new_Meeting->participants = OC_create_container((OC_comp_fp_t) compare_Person_lastname);
        
        new_Meeting->time = time;
        
        new_Meeting->topic = (char*) malloc_with_error_handling(sizeof(strlen(topic) + 1));
        strcpy(new_Meeting->topic, topic);
        
        g_string_memory += (strlen(topic) + 1);
        g_Meeting_memory++;
    }
 
    return new_Meeting;
}

void destroy_Meeting(struct Meeting* meeting_ptr) {
    if (meeting_ptr) {
        g_string_memory -= (strlen(meeting_ptr->topic) + 1);
        g_Meeting_memory--;
        
        OC_destroy_container(meeting_ptr->participants);
        free(meeting_ptr->topic);
        meeting_ptr->topic = NULL;
        free(meeting_ptr);
        meeting_ptr = NULL;
    }
    

    
}

int get_Meeting_time(const struct Meeting* meeting_ptr) {
    return meeting_ptr->time;
}
void set_Meeting_time(struct Meeting* meeting_ptr, int time) {
    meeting_ptr->time = time;
}

int add_Meeting_participant(struct Meeting* meeting_ptr, const struct Person* person_ptr) {
    
    assert(meeting_ptr);
    if (OC_find_item(meeting_ptr->participants, (void*) person_ptr)) {
        return 0;
    } else {
        OC_insert(meeting_ptr->participants, (void*) person_ptr);
        return -1;
    }
}

int is_Meeting_participant_present(const struct Meeting* meeting_ptr, const struct Person * person_ptr) {
    
    assert(meeting_ptr);
    if (OC_find_item(meeting_ptr->participants, (void*) person_ptr)) {
        return 1;
    } else {
        return 0;
    }
    
}

int remove_Meeting_participant(struct Meeting* meeting_ptr, const struct Person* person_ptr) {
    
    assert(meeting_ptr);
    if (OC_find_item(meeting_ptr->participants, (void*) person_ptr)) {
        OC_delete_item(meeting_ptr->participants,(void*) person_ptr);
        return 0;
    } else {
        return -1;
    }
}

void print_Meeting(const struct Meeting* meeting_ptr) {
    
    assert(meeting_ptr);
    printf("Meeting time: %d, Topic: %s\nParticipants:", meeting_ptr->time, meeting_ptr->topic);
    
    if (OC_get_size(meeting_ptr->participants) == 0) {
        printf("None\n");
    } else {
        printf("\n");
        OC_apply(meeting_ptr->participants, (print_Person));
    }
    
}

void save_Meeting(const struct Meeting* meeting_ptr, FILE* outfile) {
    if (outfile) {
        fprintf(outfile, "%d %s %d\n", meeting_ptr->time, meeting_ptr->topic, OC_get_size(meeting_ptr->participants));
        OC_apply_arg(meeting_ptr->participants, (OC_apply_arg_fp_t) print_Participant_lastname, outfile);
        
    } else {
        couldnt_open_file_msg();
    }
}

/* Read a Meeting's data from a file stream, create the data object and
 return a pointer to it, NULL if invalid data discovered in file.
 No check made for whether the Meeting already exists or not. The time is expressed in 12-hr form with no AM/PM.*/
struct Meeting* load_Meeting(FILE* input_file, const struct Ordered_container* people) {
    if (!input_file) {
        couldnt_open_file_msg();
        return NULL;
    }
    
    char topic[MAX_CHAR];
    int time = 0, total_participants = 0;
    struct Meeting *new_Meeting = NULL;
    
    int scan_result = fscanf(input_file, "%d %s %d\n", &time, topic, &total_participants);
    if (scan_result != 3) {
        invalid_data_msg();
        return NULL;
    }
    
    assert(time && *topic && (total_participants >= 0));
    new_Meeting = create_Meeting(time, topic);
    
    for (; total_participants > 0; total_participants--) {
        
        struct Person *found_participant = find_participant_from_infile(people, input_file);
        assert(found_participant);
        add_Meeting_participant(new_Meeting, found_participant);
    }
    
    return new_Meeting;

}


/* Helper function for save_Meeting */
void print_Participant_lastname(const struct Person * person_ptr, FILE *outfile) {
    fprintf(outfile, "%s\n", get_Person_lastname(person_ptr));
}

/* Helper function for load_Meeting */
struct Person *find_participant_from_infile(const struct Ordered_container* people, FILE *input_file) {
    char lastname[MAX_CHAR];
    struct Person* found_participant = NULL;
    
    int scan_lastname_result = fscanf(input_file, "%s", lastname);
    assert(scan_lastname_result == 1);
    
    void *found_lastname_ptr = OC_find_item_arg(people, lastname, (OC_find_item_arg_fp_t) compare_Person_with_given_lastname);
    
    if (found_lastname_ptr) {
        found_participant = OC_get_data_ptr(found_lastname_ptr);
    }
    
    return found_participant;
}


int compare_Person_with_given_lastname(const char * given_lastname, const struct Person *person_ptr ) {
    return strcmp(given_lastname, get_Person_lastname(person_ptr));
}



