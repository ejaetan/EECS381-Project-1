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
        return 0;
    } else {
        return -1;
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





