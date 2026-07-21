
#ifndef ENROLLMENT_H
#define ENROLLMENT_H

#include "student.h"
#include "course.h"
#include "grade.h"
typedef struct Enrollment {
    int enrollment_id;
    int student_id;
    int course_id;
    int professor_id;
    char semester[20];          // 2020-FALL
    char enrollment_date[20];   // 2020-09-01
    char status[20];            // Enrolled,Completed
    struct Enrollment *next;
} Enrollment;

Course* search_course(Course *head, int course_id);
int count_course_enrollments(Enrollment *eHead, int course_id);
void enroll_student(Enrollment **eHead, Course *courseHead);
void drop_student_from_course(Enrollment **head, int student_id, int course_id);
void print_student_transcript(int student_id, Enrollment *enroll_head, Grade *grade_head);
void display_student_enrollments(Enrollment *head, Course *courseHead, int student_id);
void display_course_roster(Enrollment *head, Course *courseHead, int course_id);
void free_enrollments(Enrollment **head);
Enrollment* load_enrollments_from_csv(const char *filename);
void save_enrollments_to_csv(const char *filename, Enrollment *head);


#endif
