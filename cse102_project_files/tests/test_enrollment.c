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



void test_enrollment_search_course() {
    Course *head = NULL;

    
    Course *c1 = (Course *)malloc(sizeof(Course));
    c1->course_id = 101;
    strcpy(c1->course_code, "CS101");
    c1->next = NULL;
    head = c1;

    
    Course *found = search_course(head, 101);
    assert(found != NULL);
    assert(found->course_id == 101);

    found = search_course(head, 999);
    assert(found == NULL);

    free_courses(&head);
    printf("[PASS] test_enrollment_search_course passed\n");
}

void test_count_course_enrollments() {
    Enrollment *head = NULL;

   
    Enrollment *e1 = (Enrollment *)malloc(sizeof(Enrollment));
    e1->course_id = 101;
    strcpy(e1->status, "Enrolled");
    e1->next = NULL;
    head = e1;

  
    Enrollment *e2 = (Enrollment *)malloc(sizeof(Enrollment));
    e2->course_id = 101;
    strcpy(e2->status, "Enrolled");
    e2->next = head;
    head = e2;

    
    Enrollment *e3 = (Enrollment *)malloc(sizeof(Enrollment));
    e3->course_id = 101;
    strcpy(e3->status, "Completed");
    e3->next = head;
    head = e3;

    
    assert(count_course_enrollments(head, 101) == 2);
    assert(count_course_enrollments(head, 102) == 0);

    free_enrollments(&head);
    printf("[PASS] test_count_course_enrollments passed\n");
}

void test_drop_student_logic() {
    Enrollment *head = NULL;

    
    Enrollment *e1 = (Enrollment *)malloc(sizeof(Enrollment));
    e1->student_id = 2020001;
    e1->course_id = 101;
    strcpy(e1->status, "Enrolled");
    e1->next = NULL;
    head = e1;

    
    drop_student_from_course(&head, 2020001, 101);
    
    
    assert(head == NULL);

    printf("[PASS] test_drop_student_logic passed\n");
}

void test_enrollment_list_management() {
    Enrollment *head = NULL;

    
    Enrollment *e = (Enrollment *)malloc(sizeof(Enrollment));
    e->enrollment_id = 1;
    e->next = head;
    head = e;

    assert(head != NULL);
    
    
    free_enrollments(&head);
    assert(head == NULL);

    printf("[PASS] test_enrollment_list_management passed\n");
}



int main() {
    setlocale(LC_ALL, "");
    printf("\n========== ENROLLMENT MODULE TESTS ==========\n\n");

    test_enrollment_search_course();
    test_count_course_enrollments();
    test_drop_student_logic();
    test_enrollment_list_management();

    printf("\n=============================================\n");
    printf("    ALL ENROLLMENT TESTS PASSED SUCCESSFULLY\n");
    printf("=============================================\n");

    return 0;
}