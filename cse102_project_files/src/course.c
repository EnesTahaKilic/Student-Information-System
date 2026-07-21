
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "course.h"
#include "enrollment.h"
#include "utils.h"



int is_unique_courseID(Course *head, int id) {
    while (head != NULL) {
        if (head->course_id == id)
            return 0;
        head = head->next;
    }
    return 1;
}

int is_unique_coursecode(Course *head, const char *code) {
    while (head != NULL) {
        if (strcmp(head->course_code, code) == 0)
            return 0;
        head = head->next;
    }
    return 1;
}

void add_course(Course **head) {
    Course *newCourse = malloc(sizeof(Course));
    if (!newCourse) {
        printf("Memory allocation failed.\n");
        return;
    }

    
    do {
        printf("Course ID: ");
        scanf("%d", &newCourse->course_id);

        if (newCourse->course_id <= 0){
            printf("ID must be positive.\n");
        }
        else if (!is_unique_courseID(*head, newCourse->course_id))
            printf("Course ID already exists.\n");

    } while (newCourse->course_id <= 0 || !is_unique_courseID(*head, newCourse->course_id));


    do {
        printf("Course Code: ");
        scanf("%s", newCourse->course_code);

        if (!is_unique_coursecode(*head, newCourse->course_code))
            printf("Course code already exists.\n");

    } while (!is_unique_coursecode(*head, newCourse->course_code));

    printf("Course Name: ");
    scanf(" %[^\n]", newCourse->course_name);

    
    do {
        printf("Credits (3 or 4): ");
        scanf("%d", &newCourse->credits);

        if (!is_valid_credits(newCourse->credits))
            printf("Credits must be 3 or 4.\n");

    } while (!is_valid_credits(newCourse->credits));

    
    do {
        printf("Capacity: ");
        scanf("%d", &newCourse->capacity);

        if (!is_valid_capacity(newCourse->capacity))
            printf("Capacity must be greater than 0.\n");

    } while (!is_valid_capacity(newCourse->capacity));

    
    printf("Department: ");
    scanf(" %[^\n]", newCourse->department);

    
    printf("Prerequisites (comma-separated or NONE): ");
    scanf("%s", newCourse->prerequisites);

    if (strcmp(newCourse->prerequisites, "NONE") == 0)
        newCourse->prerequisites[0] = '\0';

    newCourse->professor_id = 0;

    newCourse->next = *head;
    *head = newCourse;

    printf("Course added successfully.\n");
}

void edit_course(Course *course) {
    if (!course) {
        printf("Course not found.\n");
        return;
    }

    printf("New Course Name: ");
    scanf(" %[^\n]", course->course_name);

    do {
        printf("New Credits (3 or 4): ");
        scanf("%d", &course->credits);
    } while (!is_valid_credits(course->credits));

    do {
        printf("New Capacity: ");
        scanf("%d", &course->capacity);
    } while (!is_valid_capacity(course->capacity));

    printf("New Department: ");
    scanf(" %[^\n]", course->department);

    printf("New Prerequisites (comma-separated or NONE): ");
    scanf("%s", course->prerequisites);

    if (strcmp(course->prerequisites, "NONE") == 0)
        course->prerequisites[0] = '\0';

    printf("Course updated successfully.\n");
}

void delete_course(Course **head, int course_id)
{
    Course *current, *previous;

    
    if (head == NULL || *head == NULL) {
        printf("Course list is empty.\n");
        return;
    }

    current = *head;
    previous = NULL;


    while (current != NULL && current->course_id != course_id) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Course not found.\n");
        return;
    }

    
    if (previous == NULL) {//delete first node
        *head = current->next;
    } 
    /* Delete middle,last*/
    else {
        previous->next = current->next;
    }

    free(current);
    printf("Course deleted successfully.\n");
}

Course *search_course_bycode(Course *head, const char *course_code) {
    while (head != NULL) {
        if (strcmp(head->course_code, course_code) == 0) {
            return head;   // course found
        }
        head = head->next;
    }
    return NULL;  // course not found
}

Course *search_course_byid(Course *head, int course_id) {
    while (head != NULL) {
        if (head->course_id == course_id) {
            return head;   // course found
        }
        head = head->next;
    }
    return NULL;           // course not found
}

void display_course(const Course *course) {
    if (course == NULL) {
        printf("Course not found.\n");
        return;
    }

    printf("\n--- Course Information ---\n");
    printf("Course ID     : %d\n", course->course_id);
    printf("Course Code   : %s\n", course->course_code);
    printf("Course Name   : %s\n", course->course_name);
    printf("Credits       : %d\n", course->credits);
    printf("Capacity      : %d\n", course->capacity);
    printf("Department    : %s\n", course->department);
    printf("Professor ID  : %d\n", course->professor_id);

    if (strlen(course->prerequisites) == 0)
        printf("Prerequisites : None\n");
    else
        printf("Prerequisites : %s\n", course->prerequisites);

    printf("---------------------------\n");
}

void set_course_capacity(Course *course, int capacity)
{
    /* Validation */
    if (course == NULL) {
        printf("Course not found.\n");
        return;
    }

    if (capacity <= 0) {
        printf("Invalid capacity value.\n");
        return;
    }

    course->capacity = capacity;
    printf("Course capacity updated successfully.\n");
}

void set_prerequisites(Course *course, const char *prerequisites)
{
    if (course == NULL) {
        printf("Course not found.\n");
        return;
    }

    if (prerequisites == NULL) {
        printf("Invalid prerequisites input.\n");
        return;
    }

    // Copy prerequisites 
    strncpy(course->prerequisites, prerequisites,
            sizeof(course->prerequisites) - 1);

    course->prerequisites[sizeof(course->prerequisites) - 1] = '\0';

    printf("Prerequisites updated successfully.\n");
}

void free_courses(Course **head)
{
    Course *current;
    Course *temp;

    if (head == NULL || *head == NULL)
        return;

    current = *head;
    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }

    *head = NULL;
}

Course* load_courses_from_csv(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (!fp)
    {
        printf("Error: courses.csv could not be opened.\n");
        return NULL;
    }

    Course *head = NULL;
    char line[512];
    int count = 0;   

    fgets(line, sizeof(line), fp); // skip header

    while (fgets(line, sizeof(line), fp))
    {
        Course *c = malloc(sizeof(Course));
        if (!c)
            break;

        c->next = NULL; 

        int fields = sscanf(
            line,
            "%d,%9[^,],%49[^,],%d,%d,%49[^,],%9[^,\n]", &c->course_id, c->course_code, c->course_name, &c->credits, &c->capacity, c->department, c->prerequisites
        );

        if (fields < 6)
        {
            free(c);
            continue;
        }

        if (fields == 6)
        {
            strcpy(c->prerequisites, "NONE");
        }

        c->professor_id = 0;

        // insert to linked list (head insertion)
        c->next = head;
        head = c;

        count++; 
    }

    fclose(fp);

    printf("%d courses loaded successfully.\n", count); 
    return head;
}


void save_courses_to_csv(const char *filename, Course *head) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        printf("File could not be opened for writing.\n");
        return;
    }

    fprintf(fp, "course_id,course_code,course_name,credits,capacity,department,prerequisites\n");

    while (head) {
        fprintf(fp, "%d,%s,%s,%d,%d,%s,%s\n",
                head->course_id,
                head->course_code,
                head->course_name,
                head->credits,
                head->capacity,
                head->department,
                strlen(head->prerequisites) > 0 ? head->prerequisites : "NONE");
        head = head->next;
    }

    fclose(fp);
}

int check_prerequisites(Course *course, int student_id, void *enrollment_head, Course *course_head) {
    if (course == NULL) {
        printf("Error: Course not found.\n");
        return 0;
    }

    if (strcmp(course->prerequisites, "NONE") == 0 || 
        strcmp(course->prerequisites, "none") == 0 || 
        strlen(course->prerequisites) == 0) {
        return 1;
    }

    Enrollment *enroll = (Enrollment *)enrollment_head;
    
    while (enroll != NULL) {
        if (enroll->student_id == student_id && 
            strcmp(enroll->status, "Completed") == 0) {
            
            Course *enrolled_course = search_course_byid(course_head, enroll->course_id);
            if (enrolled_course != NULL) {
                if (strcmp(enrolled_course->course_code, course->prerequisites) == 0) {
                    return 1;
                }
            }
        }
        enroll = enroll->next;
    }

    printf("Error: Student %d has not completed prerequisite: %s\n", 
           student_id, course->prerequisites);
    return 0;
}