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


void test_search_grade_by_id() {
    Grade *head = NULL;

   
    Grade *g1 = (Grade *)malloc(sizeof(Grade));
    g1->grade_id = 50001;
    g1->student_id = 2020001;
    g1->next = NULL;
    head = g1;

    Grade *g2 = (Grade *)malloc(sizeof(Grade));
    g2->grade_id = 50002;
    g2->student_id = 2020002;
    g2->next = head;
    head = g2;

    
    Grade *found = search_grade_by_id(head, 50001);
    assert(found != NULL);
    assert(found->grade_id == 50001);

    found = search_grade_by_id(head, 50002);
    assert(found != NULL);
    assert(found->student_id == 2020002);

    found = search_grade_by_id(head, 99999);
    assert(found == NULL);

    free_grades(&head);
    printf("[PASS] test_search_grade_by_id passed\n");
}

void test_letter_grade_to_points() {
    
    assert(letter_grade_to_points("A") == 4.0);
    assert(letter_grade_to_points("B") == 3.0);
    assert(letter_grade_to_points("C") == 2.0);
    assert(letter_grade_to_points("F") == 0.0);
    
    
    assert(letter_grade_to_points("XYZ") == 0.0);
    
    printf("[PASS] test_letter_grade_to_points passed\n");
}

void test_grade_validation() {
    // is_valid_letter_grade test (A, A-, B+, B, B-, C+, C)
    assert(is_valid_letter_grade("A") == 1);
    assert(is_valid_letter_grade("B+") == 1);
    assert(is_valid_letter_grade("C") == 1);
    assert(is_valid_letter_grade("D") == 0); 
    assert(is_valid_letter_grade("F") == 0); 

    
    assert(is_valid_numeric_grade(85.0) == 1);
    assert(is_valid_numeric_grade(0.0) == 1);
    assert(is_valid_numeric_grade(100.0) == 1);
    assert(is_valid_numeric_grade(100.1) == 0);
    assert(is_valid_numeric_grade(-1.0) == 0);

    printf("[PASS] test_grade_validation passed\n");
}

void test_grade_list_management() {
    Grade *head = NULL;

   
    Grade *g = (Grade *)malloc(sizeof(Grade));
    g->grade_id = 70001;
    g->next = head;
    head = g;

    assert(head != NULL);
    assert(head->grade_id == 70001);

    
    free_grades(&head);
    assert(head == NULL);

    printf("[PASS] test_grade_list_management passed\n");
}



int main() {
    setlocale(LC_ALL, "");
    printf("\n========== GRADE MODULE TESTS ==========\n\n");

    test_search_grade_by_id();
    test_letter_grade_to_points();
    test_grade_validation();
    test_grade_list_management();

    printf("\n========================================\n");
    printf("    ALL GRADE TESTS PASSED SUCCESSFULLY\n");
    printf("========================================\n");

    return 0;
}