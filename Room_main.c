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
    
    
    

}

