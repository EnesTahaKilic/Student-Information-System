// student.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"
#include "grade.h"
#include "utils.h"

void read_string_with_spaces(char *buffer, int size)
{
    int i = 0;
    int c;
    while ((c = getchar()) != '\n' && c != EOF && i < size - 1)
    {
        buffer[i++] = c;
    }
    buffer[i] = '\0';
}

Student *add_student(Student *head)
{
    Student *new_student = malloc(sizeof(Student));
    if (new_student == NULL)
    {
        printf("Memory allocation failed!\n");
        return head;
    }

    printf("Enter student ID (YEAR###): ");
    if (scanf("%d", &new_student->id) != 1)
    {

        printf("Error: Student ID must be numeric.\n");
        clear_input_buffer();
        free(new_student);

        return head;
    }

    if (!is_valid_studentid(new_student->id))
    {
        free(new_student);
        return head;
    }

    if (search_student_byid(head, new_student->id) != NULL)
    {
        printf("Student with this ID already exists!\n");
        free(new_student);
        return head;
    }

    printf("Enter name: ");
    scanf("%49s", new_student->name);
    if (!is_valid_name(new_student->name))
    {
        free(new_student);
        return head;
    }

    printf("Enter surname: ");
    scanf("%49s", new_student->surname);
    if (!is_valid_name(new_student->surname))
    {
        free(new_student);
        return head;
    }

    printf("Enter email: ");
    scanf("%99s", new_student->email);
    if (!is_valid_email(new_student->email))
    {
        free(new_student);
        return head;
    }

    printf("Enter phone: ");
    scanf("%19s", new_student->phone);
    if (!is_valid_phone(new_student->phone))
    {
        free(new_student);
        return head;
    }

    printf("Enter enrollment year: ");
    if (scanf("%d", &new_student->enrollment_year) != 1)
    {
        printf("Error: Enrollment year must be numeric.\n");
        clear_input_buffer();
        free(new_student);
        return head;
    }

    if (!is_valid_enrollment_year(new_student->enrollment_year))
    {
        free(new_student);
        return head;
    }

    printf("Enter major: ");
    scanf("%29s", new_student->major);

    new_student->gpa = 0.0; // default assigned value

    new_student->next = head;
    head = new_student;

    printf("Student added successfully.\n");
    return head;
}

Student *search_student_byid(Student *head, int id)
{
    if (!is_valid_studentid(id))
    {
        return NULL;
    }

    Student *current = head;

    while (current != NULL)
    {
        if (current->id == id)
            return current;
        current = current->next;
    }
    return NULL;
}

Student *search_student_byname(Student *head, char *name)
{
    if (name == NULL || !is_valid_name(name))
    {
        printf("Error: Invalid name for search.\n");
        return NULL;
    }

    Student *current = head;

    while (current != NULL)
    {
        if (strcmp(current->name, name) == 0)
            return current;
        current = current->next;
    }

    return NULL;
}

Student *search_student_byemail(Student *head, char *email)
{
    Student *current = head;

    // Check if email contains '@' 
    if (strchr(email, '@') == NULL)
    {
        printf("Invalid email address! '@' symbol missing.\n");
        return NULL;
    }

    while (current != NULL)
    {
        if (strcmp(current->email, email) == 0)
        {
            return current;
        }
        current = current->next;
    }

    return NULL;
}

int edit_student(Student *head, int id)
{
    Student *student = search_student_byid(head, id);

    if (student == NULL)
    {
        printf("Student not found!\n");
        return 0;
    }

    printf("New name: ");
    scanf("%49s", student->name);
    if (!is_valid_name(student->name))
    {
        printf("Update failed: Invalid name.\n");
        return 0;
    }

    printf("New surname: ");
    scanf("%49s", student->surname);
    if (!is_valid_name(student->surname))
    {
        printf("Update failed: Invalid surname.\n");
        return 0;
    }

    printf("New email: ");
    scanf("%99s", student->email);
    if (!is_valid_email(student->email))
    {
        printf("Update failed: Invalid email.\n");
        return 0;
    }

    printf("New phone: ");
    scanf("%19s", student->phone);
    if (!is_valid_phone(student->phone))
    {
        printf("Update failed: Invalid phone number.\n");
        return 0;
    }

    printf("New enrollment year: ");
    if (scanf("%d", &student->enrollment_year) != 1)
    {
        printf("Update failed: Enrollment year must be numeric.\n");
        clear_input_buffer();
        return 0;
    }
    if (!is_valid_enrollment_year(student->enrollment_year))
    {
        printf("Update failed: Invalid enrollment year.\n");
        return 0;
    }

    printf("Enter major: ");
    scanf("%49s", student->major);

    printf("Student information updated successfully.\n");
    return 1;
}

Student *delete_student(Student *head, int id)
{

    if (!is_valid_studentid(id))
    {
        printf("Delete failed: Invalid student ID.\n");
        return head;
    }

    Student *current = head;
    Student *previous = NULL;

    while (current != NULL && current->id != id)
    {
        previous = current;
        current = current->next;
    }

    if (current == NULL)
    {
        printf("Student not found!\n");
        return head;
    }

    if (previous == NULL)
    {
        head = current->next;
    }
    else
    {
        previous->next = current->next;
    }

    free(current);
    printf("Student deleted successfully.\n");
    return head;
}

void display_student(const Student *student)
{
    if (student == NULL)
    {
        printf("Student not found.\n");
        return;
    }

    printf("ID              : %d\n", student->id);
    printf("Name            : %s\n", student->name);
    printf("Surname         : %s\n", student->surname);
    printf("Email           : %s\n", student->email);
    printf("Phone           : %s\n", student->phone);
    printf("Enrollment Year : %d\n", student->enrollment_year);
    printf("Major           : %s\n", student->major);
    printf("GPA             : %.2f\n", student->gpa);
    printf("--------------------------------------\n");
}

void display_gpa(const Student *head)
{
    int id;
    const Student *student;

    printf("Enter student ID: ");
    scanf("%d", &id);

    student = search_student_byid((Student *)head, id);

    if (student == NULL)
    {
        printf("Student not found!\n");
        return;
    }

    printf("Student GPA: %.2f\n", student->gpa);
}

void free_students(Student **head)
{
    Student *curr = *head;
    Student *temp;

    while (curr != NULL) {
        temp = curr;
        curr = curr->next;
        free(temp);
    }

    *head = NULL;
}

Student *load_students_from_csv(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (!fp)
    {
        printf("Error: students.csv could not be opened.\n");
        return NULL;
    }

    Student *head = NULL;
    Student *tail = NULL;
    char line[256];
    int count = 0; 

    fgets(line, sizeof(line), fp); // skip header

    while (fgets(line, sizeof(line), fp))
    {
        Student *s = malloc(sizeof(Student));
        if (!s)
            break;

        s->next = NULL; 

        int fields = sscanf(
            line,
            "%d,%49[^,],%49[^,],%99[^,],%19[^,],%d,%49[^,],%lf",
            &s->id, s->name, s->surname, s->email, s->phone,
            &s->enrollment_year, s->major, &s->gpa);

        if (fields != 8)
        {
            free(s);
            continue;
        }

        if (!is_valid_studentid(s->id) ||
            !is_valid_name(s->name) ||
            !is_valid_name(s->surname) ||
            !is_valid_email(s->email) ||
            !is_valid_phone(s->phone) ||
            !is_valid_enrollment_year(s->enrollment_year) ||
            !is_valid_gpa(s->gpa)){
        
            free(s);
            continue;
           }

        if (tail == NULL){
        
            head = s;
            tail = s;
        }
        else
        {
            tail->next = s;
            tail = s;
        }

        count++; 
    }

    fclose(fp);

    printf("%d students loaded successfully.\n", count); 
    return head;
}


void save_students_to_csv(const char *filename, Student *head)
{
    FILE *fp = fopen(filename, "w");
    if (!fp)
    {
        printf("File could not be opened for writing.\n");
        return;
    }

    fprintf(fp, "student_id,first_name,last_name,email,phone,enrollment_year,major,gpa\n");

    while (head)
    {
        fprintf(fp, "%d,%s,%s,%s,%s,%d,%s,%.2f\n",
                head->id,
                head->name,
                head->surname,
                head->email,
                head->phone,
                head->enrollment_year,
                head->major,
                head->gpa);
        head = head->next;
    }

    fclose(fp);
}

void calculate_student_gpa(Student *student, void *grade_head) {
    if (student == NULL || grade_head == NULL) {
        return;
    }

    Grade *g = (Grade *)grade_head;
    double total_points = 0.0;
    int total_credits = 0;
    int count = 0;

    while (g != NULL) {
        if (g->student_id == student->id) {
            double points = letter_grade_to_points(g->letter_grade);
            total_points += points;
            total_credits += 1;
            count++;
        }
        g = g->next;
    }

    if (count > 0) {
        student->gpa = total_points / (double)count;
    } else {
        student->gpa = 0.0;
    }
}

