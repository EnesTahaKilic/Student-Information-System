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



void test_data_loading(Student *s, Course *c, Enrollment *e) {
    
    assert(s != NULL);
    assert(c != NULL);
    assert(e != NULL);
    printf("[PASS] test_data_loading passed\n");
}

void test_student_history(Student *students, Enrollment *enrollments, Course *courses, Grade *grades) {
    int test_student_id = 2020001;
    Student *s = search_student_byid(students, test_student_id);
    
    
    assert(s != NULL);
    
    int sem_idx = 0;
    char semesters[20][20];
    Enrollment *e = enrollments;

    while (e != NULL) {
        if (e->student_id == test_student_id) {
            int found = 0;
            for (int i = 0; i < sem_idx; i++) {
                if (strcmp(semesters[i], e->semester) == 0) {
                    found = 1;
                    break;
                }
            }
            if (!found && sem_idx < 20) {
                strncpy(semesters[sem_idx], e->semester, 19);
                sem_idx++;
            }
        }
        e = e->next;
    }

    
    assert(sem_idx >= 2);
    printf("[PASS] test_student_history passed (Semesters: %d)\n", sem_idx);
}

void test_students_without_grades(Student *students, Grade *grades) {
    Student *s2 = students;
    int no_grade_count = 0;
    
    while (s2 != NULL) {
        Grade *g = grades;
        int has_grade = 0;
        while (g != NULL) {
            if (g->student_id == s2->id) {
                has_grade = 1;
                break;
            }
            g = g->next;
        }
        if (!has_grade) no_grade_count++;
        s2 = s2->next;
    }
    
    
    assert(no_grade_count > 0);
    printf("[PASS] test_students_without_grades passed (Found: %d)\n", no_grade_count);
}

void test_semester_statistics(Enrollment *enrollments) {
    char all_sems[100][20];
    int total_sems = 0;
    Enrollment *e = enrollments;

    while (e != NULL) {
        int found = 0;
        for (int i = 0; i < total_sems; i++) {
            if (strcmp(all_sems[i], e->semester) == 0) {
                found = 1;
                break;
            }
        }
        if (!found && total_sems < 100) {
            strncpy(all_sems[total_sems], e->semester, 19);
            total_sems++;
        }
        e = e->next;
    }

    
    assert(total_sems >= 4);
    printf("[PASS] test_semester_statistics passed (Total: %d)\n", total_sems);
}

void test_gpa_calculation(Student *students, Grade *grades) {
    Student *s3 = search_student_byid(students, 2020001);
    assert(s3 != NULL);
    
    calculate_student_gpa(s3, grades);
    
    // GPA must bebetween 0.0 and 4.0 
    assert(s3->gpa >= 0.0 && s3->gpa <= 4.0);
    printf("[PASS] test_gpa_calculation passed (GPA: %.2f)\n", s3->gpa);
}

int main() {
    printf("========== MULTI-SEMESTER TRACKING TESTS ==========\n\n");

    
    Student *students = load_students_from_csv("../data/students.csv");
    Course *courses = load_courses_from_csv("../data/courses.csv");
    Enrollment *enrollments = load_enrollments_from_csv("../data/enrollments.csv");
    Grade *grades = load_grades_from_csv("../data/grades.csv");

    
    test_data_loading(students, courses, enrollments);
    test_student_history(students, enrollments, courses, grades);
    test_students_without_grades(students, grades);
    test_semester_statistics(enrollments);
    test_gpa_calculation(students, grades);

    
    free_students(&students);
    free_courses(&courses);
    free_enrollments(&enrollments);
    free_grades(&grades);

    printf("\n===================================================\n");
    printf("   ALL MULTI-SEMESTER TESTS PASSED SUCCESSFULLY\n");
    printf("===================================================\n");

    return 0;
}