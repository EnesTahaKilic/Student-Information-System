


#ifndef GRADE_H
#define GRADE_H

typedef struct Grade {
    int grade_id;
    int enrollment_id;
    int student_id;
    int course_id;
    char letter_grade[10];
    double numeric_grade;
    char semester[20];
    struct Grade *next;
} Grade;


void add_grade(Grade **head);

void update_grade(Grade *head, int grade_id);

void calculate_course_statistics(Grade *head, int course_id);

void display_grade_distribution(Grade *head, int course_id);

double letter_grade_to_points(const char *letter_grade);

Grade* search_grade_by_id(Grade *head, int grade_id);
void free_grades(Grade **head);
Grade* load_grades_from_csv(const char *filename);
void save_grades_to_csv(const char *filename, Grade *head);

#endif








