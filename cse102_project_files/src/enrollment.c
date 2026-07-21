#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "enrollment.h"
#include "student.h"
#include "course.h"


Course* search_course(Course *head, int course_id) {
    while (head) {
        if (head->course_id == course_id)
            return head;
        head = head->next;
    }
    return NULL;
}

int count_course_enrollments(Enrollment *eHead, int course_id) {
    int count = 0;
    while (eHead) {
        if (eHead->course_id == course_id && strcmp(eHead->status, "Enrolled") == 0)
            count++;
        eHead = eHead->next;
    }
    return count;
}

void enroll_student(Enrollment **eHead, Course *courseHead) {

    int sid, cid;

    printf("Student ID: ");
    scanf("%d", &sid);

    printf("Course ID: ");
    scanf("%d", &cid);

    Course *course = search_course(courseHead, cid);
    if (!course) {
        printf("Course not found.\n");
        return;
    }

    if (!check_prerequisites(course, sid, *eHead, courseHead)) {
        printf("Prerequisites not satisfied.\n");
        return;
    }

    /* capacity */
    if (count_course_enrollments(*eHead, cid) >= course->capacity) {
        printf("Course capacity is full.\n");
        return;
    }

    Enrollment *newNode = malloc(sizeof(Enrollment));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    newNode->student_id = sid;
    newNode->course_id = cid;
    newNode->professor_id = 0;
    newNode->enrollment_id = 0; 
    
    printf("Enter Semester (e.g. 2024-FALL): ");
    scanf("%9s", newNode->semester);
    
    // Simple date - current date placeholder or ask user
    strcpy(newNode->enrollment_date, "2024-01-14"); 

    strcpy(newNode->status, "Enrolled");
    newNode->next = *eHead;
    *eHead = newNode;

    printf("Student enrolled successfully.\n");
}

void drop_student_from_course(Enrollment **head, int student_id, int course_id) {
    Enrollment *temp = *head;
    Enrollment *prev = NULL;

    while (temp) {
        if (temp->student_id == student_id && temp->course_id == course_id && strcmp(temp->status, "Enrolled") == 0) {

            if (prev == NULL)
                *head = temp->next;
            else
                prev->next = temp->next;

            free(temp);
            printf("Student dropped from course.\n");
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("Enrollment not found.\n");
}
void print_student_transcript(
    int student_id,
    Enrollment *enroll_head,
    Grade *grade_head)
{
    Enrollment *e = enroll_head;
    int found = 0;

    printf("\n----- TRANSCRIPT -----\n");

    while (e)
    {
        if (e->student_id == student_id)
        {
            found = 1;
            printf("Course ID: %d | Semester: %s",
                   e->course_id, e->semester);

            Grade *g = grade_head;
            int grade_found = 0;

            while (g)
            {
                if (g->enrollment_id == e->enrollment_id)
                {
                    printf(" | Grade: %s (%.2f)",
                           g->letter_grade,
                           g->numeric_grade);
                    grade_found = 1;
                    break;
                }
                g = g->next;
            }

            if (!grade_found)
                printf(" | Grade: N/A");

            printf("\n");
        }
        e = e->next;
    }

    if (!found)
        printf("No enrollments found for this student.\n");

    printf("----------------------\n");
}

void display_student_enrollments(Enrollment *head, Course *courseHead, int student_id) {
    int found = 0;

    while (head) {
        if (head->student_id == student_id && strcmp(head->status, "Enrolled") == 0) {

            Course *c = search_course(courseHead, head->course_id);
            if (c)
                printf("%s - %s (Semester: %s)\n", c->course_code, c->course_name, head->semester);
            found = 1;
        }
        head = head->next;
    }

    if (!found)
        printf("No active enrollments.\n");
}
void display_course_roster(Enrollment *head, Course *courseHead, int course_id) {

    Course *c = search_course(courseHead, course_id);
    if (!c) {
        printf("Course not found.\n");
        return;
    }

    char target_semester[15];
    printf("Enter Semester to filter (or type ALL): ");
    scanf("%14s", target_semester);

    printf("Course: %s - %s\n", c->course_code, c->course_name);

    int found = 0;
    while (head) {
        if (head->course_id == course_id && strcmp(head->status, "Enrolled") == 0) {
            
            if (strcmp(target_semester, "ALL") != 0 && strcmp(head->semester, target_semester) != 0) {
                head = head->next;
                continue;
            }

            printf("Student ID: %d (Semester: %s)\n", head->student_id, head->semester);
            found = 1;
        }
        head = head->next;
    }

    if (!found)
        printf("No students enrolled.\n");
}

void free_enrollments(Enrollment **head) {
    Enrollment *current = *head;
    Enrollment *temp;

    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }
    *head = NULL;
}

Enrollment* load_enrollments_from_csv(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (!fp)
    {
        printf("Error: enrollments.csv could not be opened.\n");
        return NULL;
    }

    Enrollment *head = NULL;
    char line[256];
    int count = 0;   

    fgets(line, sizeof(line), fp); 

    while (fgets(line, sizeof(line), fp))
    {
        Enrollment *e = malloc(sizeof(Enrollment));
        if (!e)
            break;

        e->next = NULL; 

        int fields = sscanf(
            line,
            "%d,%d,%d,%d,%19[^,],%19[^,],%19[^,\n]",
            &e->enrollment_id,
            &e->student_id,
            &e->course_id,
            &e->professor_id,
            e->semester,
            e->enrollment_date,
            e->status
        );

        if (fields != 7)
        {
            free(e);
            continue;
        }

    
        e->next = head;
        head = e;

        count++; 
    }

    fclose(fp);

    printf("%d enrollments loaded successfully.\n", count); 
    return head;
}


void save_enrollments_to_csv(const char *filename, Enrollment *head) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        printf("File could not be opened for writing.\n");
        return;
    }

    fprintf(fp, "enrollment_id,student_id,course_id,professor_id,semester,enrollment_date,status\n");

    while (head) {
        
        fprintf(fp, "%d,%d,%d,%d,%s,%s,%s\n", head->enrollment_id, head->student_id, head->course_id, head->professor_id, head->semester, head->enrollment_date, head->status);
        
        head = head->next;
    }

    fclose(fp);
}
