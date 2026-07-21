#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "grade.h"
#include "utils.h"


Grade* search_grade_by_id(Grade *head, int grade_id) {
    while (head) {
        if (head->grade_id == grade_id)
            return head;
        head = head->next;
    }
    return NULL;
}

void add_grade(Grade **head) {
    Grade *new_grade = malloc(sizeof(Grade));
    if (!new_grade) return;

    printf("Grade ID (5-digit): ");
    scanf("%d", &new_grade->grade_id);

    if (search_grade_by_id(*head, new_grade->grade_id)) {
        printf("Grade ID already exists.\n");
        free(new_grade);
        return;
    }

    printf("Enrollment ID: ");
    scanf("%d", &new_grade->enrollment_id);

    printf("Student ID: ");
    scanf("%d", &new_grade->student_id);

    printf("Course ID: ");
    scanf("%d", &new_grade->course_id);

    printf("Letter Grade (A–C): ");
    scanf("%9s", new_grade->letter_grade);

    if (!is_valid_letter_grade(new_grade->letter_grade)) {
        printf("Invalid letter grade.\n");
        free(new_grade);
        return;
    }

    printf("Numeric Grade (81.0–98.0): ");
    scanf("%lf", &new_grade->numeric_grade);

    if (!is_valid_numeric_grade(new_grade->numeric_grade)) {
        printf("Invalid numeric grade.\n");
        free(new_grade);
        return;
    }

    printf("Semester (e.g., 2020-FALL): ");
    scanf("%14s", new_grade->semester);

    new_grade->next = *head;
    *head = new_grade;

    printf("Grade recorded successfully.\n");
}

void update_grade(Grade *head, int grade_id) {
    Grade *g = search_grade_by_id(head, grade_id);

    if (!g) {
        printf("Grade is not found.\n");
        return;
    }

    printf("New Letter Grade: ");
    scanf("%9s", g->letter_grade);

    if (!is_valid_letter_grade(g->letter_grade)) {
        printf("Invalid letter grade.\n");
        return;
    }

    printf("New Numeric Grade: ");
    scanf("%lf", &g->numeric_grade);

    if (!is_valid_numeric_grade(g->numeric_grade)) {
        printf("Invalid numeric grade.\n");
        return;
    }

    printf("Grade updated successfully.\n");
}

void calculate_course_statistics(Grade *head, int course_id) {
    int count = 0;
    double sum = 0, min = 100, max = 0;

    while (head) {
        if (head->course_id == course_id) {
            sum += head->numeric_grade;
            if (head->numeric_grade < min) min = head->numeric_grade;
            if (head->numeric_grade > max) max = head->numeric_grade;
            count++;
        }
        head = head->next;
    }

    if (count == 0) {
        printf(" No grades found for this course.\n");
        return;
    }

    printf("\nCourse ID: %d\n", course_id);
    printf("Students: %d\n", count);
    printf("Average: %.2f\n", sum / count);
    printf("Min: %.2f\n", min);
    printf("Max: %.2f\n", max);
}

void display_grade_distribution(Grade *head, int course_id) {
    int A=0; 
    int A_=0; 
    int Bp=0; 
    int B=0;         /*A,A-,B+,B,B-,C+,C*/
    int B_=0; 
    int Cp=0; 
    int C=0;

    while (head) {
        if (head->course_id == course_id) {
            if (!strcmp(head->letter_grade, "A")) A++;
            else if (!strcmp(head->letter_grade, "A-")) A_++;
            else if (!strcmp(head->letter_grade, "B+")) Bp++;
            else if (!strcmp(head->letter_grade, "B")) B++;
            else if (!strcmp(head->letter_grade, "B-")) B_++;
            else if (!strcmp(head->letter_grade, "C+")) Cp++;
            else if (!strcmp(head->letter_grade, "C")) C++;
        }
        head = head->next;
    }

    printf("\nGrade Distribution (Course %d)\n", course_id);
    printf("A : %d\nA-: %d\nB+: %d\nB : %d\nB-: %d\nC+: %d\nC : %d\n",
           A, A_, Bp, B, B_, Cp, C);
}

void free_grades(Grade **head) {
    Grade *current = *head;
    Grade *temp;

    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }
    *head = NULL;
}

Grade* load_grades_from_csv(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (!fp)
    {
        printf("Error: grades.csv could not be opened.\n");
        return NULL;
    }

    Grade *head = NULL;
    char line[256];
    int count = 0;

    char *temp_locale = setlocale(LC_NUMERIC, NULL);
    char stored_locale[128];
    if (temp_locale) {
        strncpy(stored_locale, temp_locale, 127);
        stored_locale[127] = '\0';
    } else {
        strcpy(stored_locale, "C");
    }
    setlocale(LC_NUMERIC, "C");

    fgets(line, sizeof(line), fp); 

    while (fgets(line, sizeof(line), fp))
    {
        line[strcspn(line, "\r\n")] = '\0';
        if (strlen(line) == 0) continue;

        Grade *g = malloc(sizeof(Grade));
        if (!g) break;

        int fields = sscanf(
            line,
            "%d,%d,%d,%d,%9[^,],%lf,%19[^,\n]",
            &g->grade_id,
            &g->enrollment_id,
            &g->student_id,
            &g->course_id,
            g->letter_grade,
            &g->numeric_grade,
            g->semester
        );

        if (fields != 7) {
            free(g);
            continue;
        }

        g->next = head;
        head = g;
        count++;
    }


    fclose(fp);
    setlocale(LC_NUMERIC, stored_locale);

    printf("%d grades loaded successfully.\n", count); 
    return head;
}


void save_grades_to_csv(const char *filename, Grade *head) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        printf("File could not be opened for writing.\n");
        return;
    }

    fprintf(fp, "grade_id,enrollment_id,student_id,course_id,letter_grade,numeric_grade,semester\n");

    while (head) {
        fprintf(fp, "%d,%d,%d,%d,%s,%.2f,%s\n",
                head->grade_id,
                head->enrollment_id,
                head->student_id,
                head->course_id,
                head->letter_grade,
                head->numeric_grade,
                head->semester);
        head = head->next;
    }

    fclose(fp);
}

double letter_grade_to_points(const char *letter_grade) {
    if (strcmp(letter_grade, "A") == 0) return 4.0;
    if (strcmp(letter_grade, "A-") == 0) return 3.7;
    if (strcmp(letter_grade, "B+") == 0) return 3.3;
    if (strcmp(letter_grade, "B") == 0) return 3.0;
    if (strcmp(letter_grade, "B-") == 0) return 2.7;
    if (strcmp(letter_grade, "C+") == 0) return 2.3;
    if (strcmp(letter_grade, "C") == 0) return 2.0;
    if (strcmp(letter_grade, "C-") == 0) return 1.7;
    if (strcmp(letter_grade, "D+") == 0) return 1.3;
    if (strcmp(letter_grade, "D") == 0) return 1.0;
    if (strcmp(letter_grade, "F") == 0) return 0.0;
    return 0.0;
}
