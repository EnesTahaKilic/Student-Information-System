#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/student.h"
#include "../src/course.h"
#include "../src/professor.h"
#include "../src/enrollment.h"
#include "../src/grade.h"
#include "../src/utils.h"

#include "../src/student.c"
#include "../src/course.c"
#include "../src/professor.c"
#include "../src/enrollment.c"
#include "../src/grade.c"
#include "../src/utils.c"



void test_search_course_byid() {
    Course *head = NULL;
    
    // create data for testing
    Course *c1 = malloc(sizeof(Course));
    c1->course_id = 101;
    strcpy(c1->course_code, "CSE101");
    c1->next = NULL;
    head = c1;
    
    Course *c2 = malloc(sizeof(Course));
    c2->course_id = 102;
    strcpy(c2->course_code, "CSE102");
    c2->next = head;
    head = c2;
    

    Course *found = search_course_byid(head, 101);
    assert(found != NULL);
    assert(found->course_id == 101);
    
    found = search_course_byid(head, 999);
    assert(found == NULL);
    
    free_courses(&head);
    printf("[PASS] test_search_course_byid passed\n");
}

void test_search_course_bycode() {
    Course *head = NULL;
    Course *c1 = malloc(sizeof(Course));
    c1->course_id = 101;
    strcpy(c1->course_code, "CSE101");
    c1->next = NULL;
    head = c1;
    
    Course *found = search_course_bycode(head, "CSE101");
    assert(found != NULL);
    assert(strcmp(found->course_code, "CSE101") == 0);
    
    found = search_course_bycode(head, "INVALID");
    assert(found == NULL);
    
    free_courses(&head);
    printf("[PASS] test_search_course_bycode passed\n");
}

void test_is_unique_courseID() {
    Course *head = NULL;
    Course *c1 = malloc(sizeof(Course));
    c1->course_id = 101;
    c1->next = NULL;
    head = c1;
    
    
    assert(is_unique_courseID(head, 101) == 0);
    
    assert(is_unique_courseID(head, 999) == 1);
    
    free_courses(&head);
    printf("[PASS] test_is_unique_courseID passed\n");
}

void test_delete_course() {
    Course *head = NULL;
    
    Course *c1 = malloc(sizeof(Course));
    c1->course_id = 101;
    c1->next = NULL;
    head = c1;
    
    Course *c2 = malloc(sizeof(Course));
    c2->course_id = 102;
    c2->next = head;
    head = c2;
    
    
    delete_course(&head, 101);
    
    //check if the course exist
    assert(search_course_byid(head, 101) == NULL);
    
    // other course must be there
    assert(search_course_byid(head, 102) != NULL);
    
    free_courses(&head);
    printf("[PASS] test_delete_course passed\n");
}

void test_validation_functions() {
    
    assert(is_valid_credits(3) == 1);
    assert(is_valid_credits(4) == 1);
    assert(is_valid_credits(5) == 0);
    
    
    assert(is_valid_capacity(30) == 1);
    assert(is_valid_capacity(0) == 0);
    assert(is_valid_capacity(-5) == 0);
    
    printf("[PASS] test_validation_functions passed\n");
}


int main() {
    setlocale(LC_ALL, "");
    printf("\n========== COURSE MODULE TESTS ==========\n\n");
    
    test_search_course_byid();
    test_search_course_bycode();
    test_is_unique_courseID();
    test_delete_course();
    test_validation_functions();
    
    printf("\n=========================================\n");
    printf("    ALL COURSE TESTS PASSED SUCCESSFULLY\n");
    printf("=========================================\n");
    
    return 0;
}