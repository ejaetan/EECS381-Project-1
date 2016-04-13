#include "Person.h"
#include "Utility.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>



/* a Person consist of pointers to C-strings for names and phone number */
struct Person {
	char* firstname;
	char* lastname;
	char* phoneno;
};

struct Person* create_Person(const char* firstname, const char* lastname,
                             const char* phoneno) {
    
    struct Person *new_Person = (struct Person*) malloc_with_error_handling(sizeof(struct Person)) ;
    
    new_Person->firstname = (char*)malloc_with_error_handling(sizeof(strlen(firstname) + 1));
    new_Person->lastname = (char*)malloc_with_error_handling(sizeof(strlen(lastname) + 1));
    new_Person->phoneno = (char*)malloc_with_error_handling(sizeof(strlen(phoneno) + 1));
    
    assert(new_Person);
    strcpy(new_Person->firstname, firstname);
    strcpy(new_Person->lastname, lastname);
    strcpy(new_Person->phoneno, phoneno);
    
    g_string_memory += (strlen(firstname) +
                        strlen(lastname) +
                        strlen(phoneno) + 3);
    
    
    
    return new_Person;
}

void destroy_Person(struct Person* person_ptr) {
    assert(person_ptr);
    g_string_memory -= (strlen(person_ptr->firstname) +
                        strlen(person_ptr->lastname) +
                        strlen(person_ptr->phoneno) + 3);
    
    free(person_ptr->firstname);
    person_ptr->firstname = NULL;
    free(person_ptr->lastname);
    person_ptr->lastname = NULL;
    free(person_ptr->phoneno);
    person_ptr->phoneno = NULL;
}

const char* get_Person_lastname(const struct Person* person_ptr) {
    return person_ptr ? (const char*) person_ptr->lastname : NULL;
}

void print_Person(const struct Person* person_ptr) {
    printf("%s %s %s\n", person_ptr->firstname, person_ptr->lastname, person_ptr->phoneno);
}

void save_Person(const struct Person* person_ptr, FILE* outfile) {
    if (outfile) {
        fprintf(outfile, "%s %s %s\n", person_ptr->firstname, person_ptr->lastname, person_ptr->phoneno);
    } else {
        couldnt_open_file_msg();
    }
}

struct Person* load_Person(FILE* infile) {
    if (!infile) {
        couldnt_open_file_msg();
        return NULL;
    }
    
    char firstname[MAX_CHAR], lastname[MAX_CHAR], phoneno[MAX_CHAR];
    int scan_result = fscanf(infile, "%63s %63s %63s\n", firstname, lastname, phoneno);
    if (scan_result != 3) {
        invalid_data_msg();
        return NULL;
    }
    
    assert(*firstname && *lastname && *phoneno);
    struct Person* new_Person = create_Person(firstname, lastname, phoneno);
    return new_Person;
}


/* Helper function */
void print_person_lastname(struct Person* person_ptr) {
    assert(person_ptr);
    printf("%s\n", get_Person_lastname(person_ptr));
    
}

int compare_Person_lastname(struct Person *Person1, struct Person *Person2) {
    return strcmp(get_Person_lastname(Person1), get_Person_lastname(Person2));
    
}

