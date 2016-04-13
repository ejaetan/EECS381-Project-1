//
//  Person_main.c
//  Project 1 V2
//
//  Created by Yi Jie Tan on 3/23/16.
//  Copyright © 2016 University of Michigan. All rights reserved.
//

#include <stdio.h>
#include "Person.h"
#include "Ordered_container.h"
#include "Utility.h"

int main(void) {
    char *firstname1 = "Joan", *firstname2 = "Taylor", *firstname3 = "Marilyn";
    char *lastname1 = "River", *lastname2 = "Swift", *lastname3 = "Monroe";
    char *phoneno1 = "123", *phoneno2 = "456", *phoneno3 = "789";
    
    struct Person *Person1 =  create_Person(firstname1, lastname1, phoneno1);
    print_Person(Person1);
    print_person_lastname(Person1);

    printf("...insert two more persons..\n");
    struct Person *Person2 =  create_Person(firstname2, lastname2, phoneno2);
    struct Person *Person3 =  create_Person(firstname3, lastname3, phoneno3);

    
    struct Ordered_container *people_container = OC_create_container((OC_comp_fp_t)(compare_Person_lastname));
    
    OC_insert(people_container, Person1);
    OC_insert(people_container, Person2);
    OC_insert(people_container, Person3);
    
    OC_apply(people_container, (OC_apply_fp_t) print_Person);
    
    printf("..delete Taylor Swift..\n");
    
    void* delete_item = OC_find_item(people_container, Person2);
    destroy_Person(Person2);
    OC_delete_item(people_container, delete_item);
    
    OC_apply(people_container, (OC_apply_fp_t) print_Person);

    FILE *fp = fopen("Person_savefile.txt", "w");
    save_Person(Person1, fp);
    
    fp = fopen("Person_loadfile.txt", "r");
    
    struct Person *load_Person1 = load_Person(fp);
    print_Person(load_Person1);
    fclose(fp);
    
    return 0;
    
    
}

