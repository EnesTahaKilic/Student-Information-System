
//    student.h 



#ifndef STUDENT_H
#define STUDENT_H

typedef struct Student{
    int id;
    char name[50];
    char surname[50];
    char email[100];
    char phone[20];
    int enrollment_year;
    char major[30];
    double gpa;
    struct Student *next;
} Student;


Student* add_student(Student *head);
int edit_student(Student *head,int id);
Student* delete_student(Student *head, int id);
Student* search_student_byid(Student *head, int id);
Student* search_student_byname(Student *head, char*name);
Student* search_student_byemail(Student *head, char*email);
void display_student(const Student *head);
void  display_gpa(const Student *head);
void calculate_student_gpa(Student *student, void *grade_head);
void free_students(Student **head);
Student* load_students_from_csv(const char *filename);
void save_students_to_csv(const char *filename, Student *head);
#endif
















