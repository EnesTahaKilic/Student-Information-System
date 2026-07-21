
//menu.h
#ifndef MENU_H
#define MENU_H



#include "student.h"
#include "course.h"
#include "professor.h"
#include "enrollment.h"
#include "grade.h"
#include "utils.h"



void student_menu(Student **student_head);
void course_menu(Course **course_head);
void professor_menu(Professor **professor_head, Course *course_head);
void enrollment_menu(Enrollment **enrollment_head, Course *course_head);
void grade_menu(Grade **grade_head);
void reports_menu(Student *student_head, Course *course_head, Professor *professor_head, Enrollment *enrollment_head, Grade *grade_head);
void system_menu(Student **student_head, Course **course_head, Professor **professor_head, Enrollment **enrollment_head, Grade **grade_head);

#endif
