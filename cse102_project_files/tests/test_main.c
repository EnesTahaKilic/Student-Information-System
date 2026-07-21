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


void test_memory_allocation() {
    Student *student_head = NULL;
    Course *course_head = NULL;
    Professor *professor_head = NULL;
    
    
    for (int i = 0; i < 10; i++) {
        Student *s = malloc(sizeof(Student));
        s->id = 2024000 + i;
        s->next = student_head;
        student_head = s;
    }
    
    for (int i = 0; i < 5; i++) {
        Course *c = malloc(sizeof(Course));
        c->course_id = 100 + i;
        c->next = course_head;
        course_head = c;
    }

    free_students(&student_head);
    assert(student_head == NULL);
    
    free_courses(&course_head);
    assert(course_head == NULL);
    
    printf("[PASS] test_memory_allocation passed\n");
}

void test_linked_list_operations() {
    Student *head = NULL;
    
   
    Student *s1 = malloc(sizeof(Student));
    s1->id = 2024001;
    s1->next = NULL;
    head = s1;
    
    Student *s2 = malloc(sizeof(Student));
    s2->id = 2024002;
    s2->next = head;
    head = s2;
    
    
    assert(head->id == 2024002);
    
    
    int count = 0;
    Student *current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    assert(count == 2);
    
    
    head = delete_student(head, 2024002);
    assert(head->id == 2024001);
    assert(search_student_byid(head, 2024002) == NULL);
    
    free_students(&head);
    printf("[PASS] test_linked_list_operations passed\n");
}

void test_grade_validation() {
    
    assert(is_valid_letter_grade("A") == 1);
    assert(is_valid_letter_grade("B+") == 1);
    assert(is_valid_letter_grade("D") == 0); 
    
    
    assert(is_valid_numeric_grade(85.5) == 1);
    assert(is_valid_numeric_grade(105.0) == 0);
    assert(is_valid_numeric_grade(-5.0) == 0);
    
    printf("[PASS] test_grade_validation passed\n");
}

void test_name_validation_turkish() {
    
    assert(is_valid_name("Ali") == 1);
    assert(is_valid_name("Çiğdem") == 1);
    assert(is_valid_name("Ali123") == 0);
    assert(is_valid_name("") == 0);
    
    printf("[PASS] test_name_validation_turkish passed\n");
}



int main() {
    
    setlocale(LC_ALL, "");

    printf("\n========== INTEGRATION TESTS START ==========\n\n");
    
    test_memory_allocation();
    test_linked_list_operations();
    test_grade_validation();
    test_name_validation_turkish();
    
    printf("\n=============================================\n");
    printf("    ALL INTEGRATION TESTS PASSED SUCCESSFULLY\n");
    printf("=============================================\n");
    
    return 0;
}