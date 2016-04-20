//
//  Room_main.c
//  Project 1 V2
//
//  Created by Yi Jie Tan on 3/25/16.
//  Copyright © 2016 University of Michigan. All rights reserved.
//

#include <stdio.h>
#include "Room.h"
#include "Ordered_container.h"
#include "Utility.h"
#include "Meeting.h"

int main(void) {
    char* topic1 = "Hello";
    int time1 = 10;
    int room1 = 1001;
    
    struct Meeting* Meeting1 = create_Meeting(time1, topic1);
    struct Room* Room1 = create_Room(room1);
    
    printf("%d\n", add_Room_Meeting(Room1, Meeting1));  // 0
    printf("%d\n", add_Room_Meeting(Room1, Meeting1));  // -1
    
    print_Meeting(find_Room_Meeting(Room1, time1));
    
    printf("%d\n", remove_Room_Meeting(Room1, Meeting1));   // 0
    printf("%d\n", remove_Room_Meeting(Room1, Meeting1));   // -1
    
    printf("%d\n", add_Room_Meeting(Room1, Meeting1));  // 0
    clear_Room(Room1);
    
    print_Room(Room1);
    
    
    const char *topicA = "Whisky", *topicB = "Tango";
    const char *firstname1 = "Bo", *lastname1 = "Jackson", *phoneno1 = "123";
    const char *firstname2 = "Mike", *lastname2 = "David", *phoneno2 = "456";
    
    struct Person* person1 = create_Person(firstname1, lastname1, phoneno1);
    struct Person* person2 = create_Person(firstname2, lastname2, phoneno2);
    
    
    struct Meeting *new_Meeting1 = create_Meeting(10, topicA);
    struct Meeting *new_Meeting2 = create_Meeting(9, topicB);

    struct Ordered_container* people = OC_create_container((OC_comp_fp_t) compare_Person_lastname);
    OC_insert(people, person1);
    OC_insert(people, person2);
    struct Room* room2 = create_Room(1000);
    
    
    add_Meeting_participant(new_Meeting1, person1);
    add_Meeting_participant(new_Meeting1, person2);
    
    add_Room_Meeting(room2, new_Meeting1);
    add_Room_Meeting(room2, new_Meeting2);

    printf("\n...saveload/file...\n");
    FILE *fp = fopen("Room_savefile.txt", "w");
    save_Room(room2, fp);
    fclose(fp);
    
    fp = fopen("Room_savefile.txt", "r");
    struct Room *new_Room = load_Room(fp, people);
    print_Room(new_Room);
    
    fclose(fp);
    

}

