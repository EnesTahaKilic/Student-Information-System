
#ifndef PROFESSOR_H
#define PROFESSOR_H

#include "course.h"

typedef struct Professor {
    int professor_id;                     
    char first_name[10];              
    char last_name[50];              
    char email[100];
    char phone[20];
    char department[30]; 
    char title[20];
    char office[10];  
    struct Professor *next;               
} Professor;

void add_professor(Professor **head);
void edit_professor(Professor *head);
void delete_professor(Professor **head);
Professor* search_professor(Professor *head, int professor_id);
void display_professor(Professor *head);
void assign_professor_to_course(Professor *pHead, Course *cHead);
void free_professors(Professor **head);
Professor* load_professors_from_csv(const char *filename);
void save_professors_to_csv(const char *filename, Professor *head);

#endif 