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
    
    struct Meeting *new_Meeting1 = create_Meeting(10, topic1);
    
    printf("%d\n", get_Meeting_time(new_Meeting1));
    
    return 0;
}
