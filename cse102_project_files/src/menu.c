
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "student.h" 
#include "course.h" 
#include "grade.h" 
#include "enrollment.h" 
#include "menu.h" 
#include "professor.h" 
#include "utils.h"


void student_menu(Student **student_head){

    int choice, id;
    Student *found = NULL;
    char search_name[50];
    char search_email[100];

    do {
        printf("\n--- Student Management Menu ---\n");
        printf("1. Add student\n");
        printf("2. Edit student\n");
        printf("3. Delete student\n");
        printf("4. Search student by ID\n");
        printf("5. Search student by Name\n");
        printf("6. Search student by Email\n");
        printf("7. Display student details and transcript\n");
        printf("8. Display student gpa\n");
        printf("0. Back to main menu\n");
        printf("Choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                *student_head = add_student(*student_head);
                break;

            case 2:
                printf("Enter student ID: ");
                
                if (scanf("%d", &id) != 1) {
                    printf("Error: ID must be numeric.\n");
                    clear_input_buffer();
                    break;
                }

                edit_student(*student_head, id);
                clear_input_buffer();

                break;

            case 3:
                printf("Enter student ID: ");
                
                if (scanf("%d", &id) != 1) {
                    printf("Error: ID must be numeric.\n");
                    clear_input_buffer();
                break;
                }

                *student_head = delete_student(*student_head, id);
                break;


            case 4:
                printf("Enter student ID: ");
                scanf("%d", &id);
                getchar();
                found = search_student_byid(*student_head, id);
                if (found)
                    display_student(found);
                else
                    printf("Student not found.\n");
                break;

            case 5:
                printf("Enter student name: ");
                scanf("%49s", search_name);
                getchar();
                found = search_student_byname(*student_head, search_name);
                if (found)
                    display_student(found);
                else
                    printf("Student not found.\n");
                break;

            case 6:
                printf("Enter student email: ");
                scanf("%99s", search_email);
                getchar();
                found = search_student_byemail(*student_head, search_email);
                if (found)
                    display_student(found);
                else
                    printf("Student not found.\n");
                break;

            case 7:
                printf("Enter student ID (YEAR###): ");
                scanf("%d", &id);

                found = search_student_byid(*student_head, id);
                display_student(found);
                break;

            case 8:
                display_gpa(*student_head);
                break;

            case 0:
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while (choice != 0);



}

void course_menu(Course **course_head)
{
    int choice;
    int id, capacity;
    Course *course;
    char code[10];
    char prereq[50];

    do {
        printf("\n--- Course Management Menu ---\n");
        printf("1. Add new course\n");
        printf("2. Edit course information\n");
        printf("3. Delete course\n");
        printf("4. Search course by ID\n");
        printf("5. Search course by Code\n");
        printf("6. Display course details\n");
        printf("7. Set course capacity\n");
        printf("8. Assign prerequisites\n");
        printf("0. Back to main menu\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice) {

        case 1:
            add_course(course_head);
            break;

        case 2:
            printf("Enter course ID to edit: ");
            scanf("%d", &id);

            course = search_course_byid(*course_head, id);
            if (course == NULL) {
                printf("Course not found.\n");
            } else {
                edit_course(course);
            }
            break;

        case 3:
            printf("Enter course ID to delete: ");
            scanf("%d", &id);

            delete_course(course_head, id);
            break;

        case 4:
            printf("Enter course ID: ");
            scanf("%d", &id);

            course = search_course_byid(*course_head, id);
            if (course == NULL)
                printf("Course not found.\n");
            else
                display_course(course);
            break;

        case 5:
            printf("Enter course code: ");
            scanf("%s", code);

            course = search_course_bycode(*course_head, code);
            if (course == NULL)
                printf("Course not found.\n");
            else
                display_course(course);
            break;

        case 6:
            printf("Enter course ID: ");
            scanf("%d", &id);

            course = search_course_byid(*course_head, id);
            if (course == NULL)
                printf("Course not found.\n");
            else
                display_course(course);
            break;

        case 7:
            printf("Enter course ID: ");
            scanf("%d", &id);

            course = search_course_byid(*course_head, id);
            if (course == NULL) {
                printf("Course not found.\n");
                break;
            }

            printf("Enter new capacity: ");
            scanf("%d", &capacity);

            set_course_capacity(course, capacity);
            break;

        case 8:
            printf("Enter course ID: ");
            scanf("%d", &id);

            course = search_course_byid(*course_head, id);
            if (course == NULL) {
                printf("Course not found.\n");
                break;
            }

            printf("Enter prerequisite course CODE (e.g., CS101) or NONE: ");
            scanf(" %[^\n]", prereq);

            set_prerequisites(course, prereq);
            break;

        case 0:
            printf("Returning to main menu...\n");
            break;

        default:
            printf("Invalid choice.\n");
        }

    } while (choice != 0);
}



void professor_menu(Professor **head, Course *course_head) {

    int choice;
    int id;
    Professor *prof;

    do {
        printf("\n===== Professor Management =====\n");
        printf("1. Add Professor\n");
        printf("2. Edit Professor\n");
        printf("3. Delete Professor\n");
        printf("4. Search Professor\n");
        printf("5. Display All Professors\n");
        printf("6. Assign Course to Professor\n");
        printf("0. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_professor(head);
                break;

            case 2:
                edit_professor(*head);
                break;
            
            case 3:
                delete_professor(head);
                break;

            case 4:
                printf("Enter Professor ID: ");
                scanf("%d", &id);
                prof = search_professor(*head, id);
                if (prof) {
                    printf("Professor Found: %s %s (%s)\n", prof->first_name, prof->last_name, prof->department);
                } else {
                    printf("Professor not found.\n");
                }
                break;

            case 5:
                display_professor(*head);
                break;

            case 6:
                assign_professor_to_course(*head, course_head);
                break;

            case 0:
                printf("Returning to main menu...\n");
                break;

            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 0);
}

void enrollment_menu(Enrollment **enrollment_head, Course *course_head) {
    int choice, student_id, course_id;

    do {
        printf("\n===== ENROLLMENT MANAGEMENT =====\n");
        printf("1. Enroll student in course\n");
        printf("2. Drop student from course\n");
        printf("3. Display student's active enrollments\n");
        printf("4. Display course roster\n");
        printf("0. Back\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            enroll_student(enrollment_head, course_head);
            break;

        case 2:
            printf("Student ID: ");
            scanf("%d", &student_id);
            printf("Course ID: ");
            scanf("%d", &course_id);
            drop_student_from_course(enrollment_head, student_id, course_id);
            break;

        case 3:
            printf("Student ID: ");
            scanf("%d", &student_id);
            display_student_enrollments(*enrollment_head, course_head, student_id);
            break;

        case 4:
            printf("Course ID: ");
            scanf("%d", &course_id);
            display_course_roster(*enrollment_head, course_head, course_id);
            break;

        case 0:
            break;

        default:
            printf("Invalid choice.\n");
        }
    } while (choice != 0);
}


void grade_menu(Grade **grade_head) {
    int choice;
    int grade_id, course_id;

    do {
        printf("\n===== GRADE MANAGEMENT =====\n");
        printf("1. Record Grade\n");
        printf("2. Update Grade\n");
        printf("3. Calculate Course Statistics\n");
        printf("4. Display Grade Distribution\n");
        printf("0. Back to Main Menu\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_grade(grade_head);
                break;

            case 2:
                printf("Enter Grade ID to update: ");
                scanf("%d", &grade_id);
                update_grade(*grade_head, grade_id);
                break;

            case 3:
                printf("Enter Course ID: ");
                scanf("%d", &course_id);
                calculate_course_statistics(*grade_head, course_id);
                break;

            case 4:
                printf("Enter Course ID: ");
                scanf("%d", &course_id);
                display_grade_distribution(*grade_head, course_id);
                break;

            case 0:
                printf("Returning to main menu...\n");
                break;

            default:
                printf("Invalid choice.\n");
        }

    } while (choice != 0);
}

void reports_menu(Student *student_head, Course *course_head, Professor *professor_head, Enrollment *enrollment_head, Grade *grade_head){
    int choice;
    
    do {
        printf("\n===== REPORTS =====\n");
        printf("1. Student Multi-Semester Course History\n");
        printf("2. Students Without Grades\n");
        printf("3. Course Enrollment Numbers\n");
        printf("4. Professor Teaching Load\n");
        printf("5. Calculate and Update Student GPAs\n");
        printf("6. View All Semesters\n");
        printf("7. Prerequisite Validation\n");
        printf("0. Back\n");
        printf("Choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();
        
        switch(choice) {
            case 1: {
                int student_id;
                printf("Enter student ID: ");
                scanf("%d", &student_id);
                clear_input_buffer();
                
                Student *s = search_student_byid(student_head, student_id);
                if (s == NULL) {
                    printf("Student not found.\n");
                    break;
                }
                
                printf("\n=== Course History for %s %s (ID: %d) ===\n", s->name, s->surname, s->id);
                
                Enrollment *e = enrollment_head;
                int found = 0;
                while (e != NULL) {
                    if (e->student_id == student_id) {
                        Course *c = search_course_byid(course_head, e->course_id);
                        Grade *g = grade_head;
                        char grade_str[10] = "N/A";
                        
                        while (g != NULL) {
                            if (g->student_id == student_id && g->course_id == e->course_id) {
                                strncpy(grade_str, g->letter_grade, 9);
                                break;
                            }
                            g = g->next;
                        }
                        
                        if (c != NULL) {
                            printf("Semester: %s | Course: %s (%s) | Grade: %s | Status: %s\n", 
                                   e->semester, c->course_code, c->course_name, grade_str, e->status);
                        }
                        found = 1;
                    }
                    e = e->next;
                }
                
                if (!found) {
                    printf("No enrollment records found.\n");
                }
                break;
            }
            
            case 2: {
                printf("\n=== Students Without Grades ===\n");
                Student *s = student_head;
                int count = 0;
                
                while (s != NULL) {
                    Grade *g = grade_head;
                    int has_grade = 0;
                    
                    while (g != NULL) {
                        if (g->student_id == s->id) {
                            has_grade = 1;
                            break;
                        }
                        g = g->next;
                    }
                    
                    if (!has_grade) {
                        printf("ID: %d | Name: %s %s | Major: %s\n", 
                               s->id, s->name, s->surname, s->major);
                        count++;
                    }
                    s = s->next;
                }
                
                printf("Total students without grades: %d\n", count);
                break;
            }
            
            case 3: {
                printf("\n=== Course Enrollment Numbers ===\n");
                Course *c = course_head;
                
                while (c != NULL) {
                    int enrolled = 0;
                    Enrollment *e = enrollment_head;
                    
                    while (e != NULL) {
                        if (e->course_id == c->course_id) {
                            enrolled++;
                        }
                        e = e->next;
                    }
                    
                    printf("Course: %s (%s) | Enrolled: %d/%d | Dept: %s\n", 
                           c->course_code, c->course_name, enrolled, c->capacity, c->department);
                    c = c->next;
                }
                break;
            }
            
            case 4: {
                printf("\n=== Professor Teaching Load ===\n");
                Professor *p = professor_head;
                
                while (p != NULL) {
                    int course_count = 0;
                    Enrollment *e = enrollment_head;
                    
                    while (e != NULL) {
                        if (e->professor_id == p->professor_id) {
                            course_count++;
                        }
                        e = e->next;
                    }
                    
                    printf("Prof: %s %s | ID: %d | Dept: %s | Enrollments: %d\n", 
                           p->first_name, p->last_name, p->professor_id, p->department, course_count);
                    p = p->next;
                }
                break;
            }
            
            case 5: {
                printf("\n=== Calculating GPAs ===\n");
                Student *s = student_head;
                int count = 0;
                
                while (s != NULL) {
                    double old_gpa = s->gpa;
                    calculate_student_gpa(s, grade_head);
                    
                    if (old_gpa != s->gpa) {
                        printf("Student %d (%s %s): GPA updated %.2f -> %.2f\n", 
                               s->id, s->name, s->surname, old_gpa, s->gpa);
                        count++;
                    }
                    s = s->next;
                }
                
                printf("Total GPAs updated: %d\n", count);
                break;
            }
            
            case 6: {
                printf("\n=== All Semesters in System ===\n");
                Enrollment *e = enrollment_head;
                char semesters[100][20];
                int sem_count = 0;
                
                while (e != NULL) {
                    int found = 0;
                    for (int i = 0; i < sem_count; i++) {
                        if (strcmp(semesters[i], e->semester) == 0) {
                            found = 1;
                            break;
                        }
                    }
                    
                    if (!found && sem_count < 100) {
                        strncpy(semesters[sem_count], e->semester, 19);
                        sem_count++;
                    }
                    e = e->next;
                }
                
                for (int i = 0; i < sem_count; i++) {
                    int enroll_count = 0;
                    Enrollment *temp = enrollment_head;
                    
                    while (temp != NULL) {
                        if (strcmp(temp->semester, semesters[i]) == 0) {
                            enroll_count++;
                        }
                        temp = temp->next;
                    }
                    
                    printf("Semester: %s | Total Enrollments: %d\n", semesters[i], enroll_count);
                }
                break;
            }
            
            case 7: {
                printf("\n=== Prerequisite Validation ===\n");
                printf("Enter course ID to check: ");
                int course_id;
                scanf("%d", &course_id);
                clear_input_buffer();
                
                Course *c = search_course_byid(course_head, course_id);
                if (c == NULL) {
                    printf("Course not found.\n");
                    break;
                }
                
                printf("Course: %s (%s)\n", c->course_code, c->course_name);
                printf("Prerequisites: %s\n", c->prerequisites);
                
                printf("Enter student ID to validate: ");
                int student_id;
                scanf("%d", &student_id);
                clear_input_buffer();
                
                if (check_prerequisites(c, student_id, enrollment_head, course_head)) {
                    printf("Student %d meets all prerequisites for this course.\n", student_id);
                } else {
                    printf("Student %d does NOT meet prerequisites.\n", student_id);
                }
                break;
            }
            
            case 0:
                printf("Returning to main menu...\n");
                break;
                
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 0);
}

void system_menu(Student **student_head,
                 Course **course_head,
                 Professor **professor_head,
                 Enrollment **enrollment_head,
                 Grade **grade_head)
{
    int choice;

    do {
        printf("\n===== SYSTEM OPTIONS =====\n");
        printf("1. Save All Data\n");
        printf("2. Load All Data\n");
        printf("3. Data Backup\n");
        printf("0. Back to Main Menu\n");
        printf("Choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();

        switch (choice) {

        case 1:
            save_students_to_csv("data/students.csv", *student_head);
            save_courses_to_csv("data/courses.csv", *course_head);
            save_professors_to_csv("data/professors.csv", *professor_head);
            save_enrollments_to_csv("data/enrollments.csv", *enrollment_head);
            save_grades_to_csv("data/grades.csv", *grade_head);

            printf("All data saved successfully.\n");
            break;

        case 2:
            /* Free data */
            free_students(student_head);
            free_courses(course_head);
            free_professors(professor_head);
            free_enrollments(enrollment_head);
            free_grades(grade_head);

            
            *student_head    = load_students_from_csv("data/students.csv");
            *course_head     = load_courses_from_csv("data/courses.csv");
            *professor_head  = load_professors_from_csv("data/professors.csv");
            *enrollment_head = load_enrollments_from_csv("data/enrollments.csv");
            *grade_head      = load_grades_from_csv("data/grades.csv");

            if (*student_head == NULL || *course_head == NULL || *professor_head == NULL) {
                printf("ERROR: One or more data files could not be loaded.\n");
            } else {
                printf("All data loaded successfully.\n");
            }
            break;

        case 3:
            
              
            if (backup_file("data/students.csv", "backup/students_backup.csv") &&
                backup_file("data/courses.csv", "backup/courses_backup.csv") &&
                backup_file("data/professors.csv", "backup/professors_backup.csv") &&
                backup_file("data/enrollments.csv", "backup/enrollments_backup.csv") &&
                backup_file("data/grades.csv", "backup/grades_backup.csv")) {

                printf("Backup completed successfully.\n");
            } else {
                printf("Backup failed.\n");
             }
            break;


        case 0:
            printf("Returning to main menu...\n");
            break;

        default:
            printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 0);
}
