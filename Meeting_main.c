//
//  Meeting_main.c
//  Project 1 V2
//
//  Created by Yi Jie Tan on 3/23/16.
//  Copyright © 2016 University of Michigan. All rights reserved.
//
#include "Meeting.h"
#include "Utility.h"
#include "Person.h"
#include "Ordered_container.h"
#include <stdio.h>

int main(void) {
    
    const char *topic1 = "Whisky", *topic2 = "Tango", *topic = "Chacha";
    const char *firstname1 = "Bo", *lastname1 = "Jackson", *phoneno1 = "123";
    const char *firstname2 = "Mike", *lastname2 = "David", *phoneno2 = "456";
    
    struct Person* person1 = create_Person(firstname1, lastname1, phoneno1);
    struct Person* person2 = create_Person(firstname2, lastname2, phoneno2);
    struct Meeting *new_Meeting1 = create_Meeting(10, topic1);
    
   
    printf("%d\n", get_Meeting_time(new_Meeting1)); // 10
    
    set_Meeting_time(new_Meeting1, 11);
    printf("%d\n", get_Meeting_time(new_Meeting1)); // 11
    
    int add_result = add_Meeting_participant(new_Meeting1, person1);
    printf("%d\n", add_result);         // -1
    
    add_result = add_Meeting_participant(new_Meeting1, person1);
    printf("%d\n", add_result);         // 0
    
    int delete_result = remove_Meeting_participant(new_Meeting1, person1);
    printf("%d\n", delete_result);      // 0

    delete_result = remove_Meeting_participant(new_Meeting1, person1);
    printf("%d\n", delete_result);      // -1

    int participants_exist = is_Meeting_participant_present(new_Meeting1, person2);
    printf("%d\n", participants_exist); // 0
    
    participants_exist = is_Meeting_participant_present(new_Meeting1, person1);
    printf("%d\n", participants_exist); //0
    
    struct Ordered_container* people = OC_create_container((OC_comp_fp_t) compare_Person_lastname);
    OC_insert(people, person1);
    OC_insert(people, person2);
    
    
    add_Meeting_participant(new_Meeting1, person1);
    add_Meeting_participant(new_Meeting1, person2);
    
    print_Meeting(new_Meeting1);
    
    FILE *fp = fopen("Meeting_savefile.txt", "w");
    save_Meeting(new_Meeting1, fp);
    
    fclose(fp);
        
    fp = fopen("Meeting_savefile.txt", "r");
    struct Meeting *load_Meeting1 = load_Meeting(fp, people);
    print_Meeting(load_Meeting1);
    
    fclose(fp);
    
    return 0;
}
