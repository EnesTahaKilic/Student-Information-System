#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <locale.h>
#include "student.h" 
#include "course.h" 
#include "grade.h" 
#include "enrollment.h" 
#include "menu.h" 
#include "professor.h" 
#include "utils.h" 

void main_menu(Student **student_head,Course **course_head,Professor **professor_head,Enrollment **enrollment_head,Grade **grade_head);

int main() {
    
    setlocale(LC_ALL, "");
    Student *student_head = NULL;
    Course *course_head = NULL;
    Professor *professor_head = NULL;
    Enrollment *enrollment_head = NULL;
    Grade *grade_head = NULL;
    
    student_head = load_students_from_csv("data/students.csv");
course_head = load_courses_from_csv("data/courses.csv");
professor_head = load_professors_from_csv("data/professors.csv");
enrollment_head = load_enrollments_from_csv("data/enrollments.csv");
grade_head = load_grades_from_csv("data/grades.csv");

main_menu(&student_head, &course_head, &professor_head, &enrollment_head, &grade_head);

save_students_to_csv("data/students.csv", student_head);
save_courses_to_csv("data/courses.csv", course_head);
save_professors_to_csv("data/professors.csv", professor_head);
save_enrollments_to_csv("data/enrollments.csv", enrollment_head);
save_grades_to_csv("data/grades.csv", grade_head);

    free_students(&student_head);
    free_courses(&course_head);
    free_professors(&professor_head);
    free_enrollments(&enrollment_head);
    free_grades(&grade_head);

    return 0;
}


void main_menu(Student **student_head,Course **course_head,Professor **professor_head,Enrollment **enrollment_head,Grade **grade_head){
    int choice;

    do {
        printf("\n===== STUDENT INFORMATION SYSTEM =====\n");
        printf("1. Student Management\n");
        printf("2. Course Management\n");
        printf("3. Professor Management\n");
        printf("4. Enrollment Management\n");
        printf("5. Grade Management\n");
        printf("6. Reports\n");
        printf("7. System Options\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);
        getchar(); 

        switch (choice) {
            case 1:
                student_menu(student_head);
                break;
            case 2:
                course_menu(course_head);
                break;
            case 3:
                professor_menu(professor_head, *course_head);
                break;
            case 4:
                enrollment_menu(enrollment_head, *course_head);
                break;
            case 5:
                grade_menu(grade_head);
                break;
            case 6:
                reports_menu(*student_head, *course_head, *professor_head, *enrollment_head, *grade_head);
                break;
            case 7:
                system_menu(student_head, course_head, professor_head, enrollment_head, grade_head);
                break;
            case 0:
                printf("Exiting system...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }

    } while (choice != 0);


}