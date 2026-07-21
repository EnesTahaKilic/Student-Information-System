#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>


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



void test_search_professor() {
    Professor *head = NULL;

    
    Professor *p1 = (Professor *)malloc(sizeof(Professor));
    p1->professor_id = 1001;
    strcpy(p1->first_name, "Ahmet");
    p1->next = NULL;
    head = p1;

    
    Professor *found = search_professor(head, 1001);
    assert(found != NULL);
    assert(found->professor_id == 1001);

    found = search_professor(head, 9999);
    assert(found == NULL);

    free_professors(&head);
    printf(" test_search_professor passed\n");
}

void test_professor_validation() {
    
    assert(is_valid_name("Ahmet") == 1); 
    assert(is_valid_name("Ayşe") == 1);   
    assert(is_valid_name("Ahmet123") == 0); 

    assert(is_valid_email("prof@uni.edu") == 1);
    assert(is_valid_email("invalid-email") == 0);
    assert(is_valid_email("@no-name.com") == 0);

    //  is_valid_phone test (555-#### format)
    assert(is_valid_phone("555-1234") == 1);
    assert(is_valid_phone("555-ABCD") == 0); // only numerical
    assert(is_valid_phone("123-4567") == 0); // 555 

    printf(" test_professor_validation passed\n");
}

void test_assign_professor_logic() {
    Professor *pList = (Professor *)malloc(sizeof(Professor));
    pList->professor_id = 500;
    pList->next = NULL;

    Course *cList = (Course *)malloc(sizeof(Course));
    cList->course_id = 101;
    cList->professor_id = 0;
    cList->next = NULL;

    
    Professor *prof = search_professor(pList, 500);
    Course *course = search_course_byid(cList, 101);

    assert(prof != NULL && course != NULL);
    course->professor_id = prof->professor_id;
    assert(course->professor_id == 500);

    free_professors(&pList);
    free_courses(&cList);
    printf(" test_assign_professor_logic passed\n");
}

void test_professor_list_management() {
    Professor *head = NULL;

    Professor *p = (Professor *)malloc(sizeof(Professor));
    p->professor_id = 2001;
    p->next = head;
    head = p;

    assert(head != NULL);
    free_professors(&head);
    assert(head == NULL); // free_professors sonrası pointer NULL olmalı

    printf(" test_professor_list_management passed\n");
}

// --- ANA TEST ÇALIŞTIRICI ---

int main() {
    
    setlocale(LC_ALL, "");

    printf("\n========== PROFESSOR & UTILS INTEGRATION TESTS ==========\n\n");

    test_search_professor();
    test_professor_validation();
    test_assign_professor_logic();
    test_professor_list_management();

    printf("\n========================================================\n");
    printf("      ALL PROFESSOR MODULE TESTS PASSED SUCCESSFULLY\n");
    printf("========================================================\n");

    return 0;
}