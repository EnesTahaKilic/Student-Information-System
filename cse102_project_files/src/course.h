

#ifndef COURSE_H
#define COURSE_H


typedef struct Course {
    int course_id;                     
    char course_code[10];              
    char course_name[50];              
    int credits;                       
    int capacity;                      
    char department[50];               
    char prerequisites[10];
    int professor_id;           
    struct Course *next;               
} Course;

int is_unique_courseID(Course *head, int id);

int is_unique_coursecode(Course *head, const char *code);

void add_course(Course **head);

void edit_course(Course *course);

void delete_course(Course **head, int course_id);

Course *search_course_bycode(Course *head, const char *course_code);

Course *search_course_byid(Course *head, int course_id);

void display_course(const Course *course);

void set_course_capacity(Course *course, int capacity);

void set_prerequisites(Course *course, const char *prerequisites);

int check_prerequisites(Course *course, int student_id, void *enrollment_head, Course *course_head);

void free_courses(Course **head);

Course* load_courses_from_csv(const char *filename);
void save_courses_to_csv(const char *filename, Course *head);

#endif 
