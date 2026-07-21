
#include<stdio.h>
#include<string.h>
#include <ctype.h>
#include "student.h"
#include "course.h"
#include "professor.h"
#include "enrollment.h"
#include "grade.h"
#include "utils.h"
#include <locale.h>

/*I will use these functions inside of another functions*/
void trim_newline(char *str)
{
    str[strcspn(str, "\r\n")] = '\0';
}


void clear_input_buffer(void) {
    while (getchar() != '\n');
}

int is_valid_studentid(int id){
    if (id < 2000000 || id > 2025999) {
        printf("Error: Student ID must be in format YEAR### (example: 2020001).\n");
        printf("Valid range: 2000000 to 2030999\n");
        return 0;
    }

    int year = id / 1000;
    int sequence = id % 1000;

    if (year < 2000 || year > 2025) {
        printf("Error: Year part must be between 2000 and 2030.\n");
        return 0;
    }

    if (sequence < 1 || sequence > 999) {
        printf("Error: Sequence number must be between 001 and 999.\n");
        return 0;
    }

    return 1;
}



int is_valid_name(const char *name){
    if (name == NULL || name[0] == '\0') return 0;

    for (int i = 0; name[i] != '\0'; i++) {
        unsigned char c = (unsigned char)name[i]; 

        if (isalpha(c) || isspace(c) || c > 127) {
            continue;
        } 
        else {
            printf("invalid character found:\n" );
            return 0; 
        }
    }
    
    return 1;
}

int is_valid_email(const char *email) {
    if (email == NULL || strlen(email) == 0) {
        printf("Error: Email cannot be empty.\n");
        return 0;
    }

    if (strlen(email) > 99) {
        printf("Error: Email too long (max 99 characters).\n");
        return 0;
    }

    const char *atsymbol = strchr(email, '@');
    if (atsymbol == NULL) {
        printf("Error: Email must contain @ symbol.\n");
        return 0;
    }

    if (atsymbol == email) {
        printf("Error: Email cannot start with @ symbol.\n");
        return 0;
    }

    const char *dotsymbol = strrchr(email, '.');
    if (dotsymbol == NULL) {
        printf("Error: Email must contain a domain extension (example: .com, .edu).\n");
        return 0;
    }

    if (dotsymbol <= atsymbol) {
        printf("Error: Invalid email format. Use format: name@domain.com\n");
        return 0;
    }

    if (strlen(dotsymbol) < 3) {
        printf("Error: Domain extension too short.\n");
        return 0;
    }

    return 1;
}

int is_valid_phone(const char *phone) {
    if (phone == NULL || strlen(phone) == 0) {
        printf("Error: Phone number cannot be empty.\n");
        return 0;
    }

    if (strlen(phone) != 8) {
        printf("Error: Phone must be exactly 8 characters (format: 555-####).\n");
        printf("Example: 555-0123\n");
        return 0;
    }

    if (strncmp(phone, "555-", 4) != 0) {
        printf("Error: Phone must start with 555- prefix.\n");
        return 0;
    }

    if (phone[3] != '-') {
        printf("Error: Fourth character must be a dash (-).\n");
        return 0;
    }

    for (int i = 4; i < 8; i++) {
        if (!isdigit((unsigned char)phone[i])) {
            printf("Error: Last 4 characters must be digits (0-9).\n");
            printf("Invalid character found: %c\n", phone[i]);
            return 0;
        }
    }

    return 1;
}



int is_valid_enrollment_year(int year){
    if (year < 2000 || year > 2025) {
        printf("Error: Enrollment year must be between 2000 and 2025.\n");
        printf("You entered: %d\n", year);
        return 0;
    }
    return 1;
}

int is_valid_gpa(double gpa){
    if (gpa < 0.0 || gpa > 4.0) {
        printf("Error: GPA must be between 0.0 and 4.0.\n");
        printf("You entered: %.2f\n", gpa);
        return 0;
    }
    return 1;
}

int is_valid_credits(int credits) {
    return (credits == 3 || credits == 4);
}

int is_valid_capacity(int capacity) {
    return capacity > 0;
}

int is_valid_letter_grade(const char *grade) {
    const char *valid_grades[] = {
        "A", "A-", "B+", "B", "B-", "C+", "C"
    };

    for (int i = 0; i < 7; i++) {
        if (strcmp(grade, valid_grades[i]) == 0)
            return 1;
    }
    return 0;
}

int is_valid_numeric_grade(double grade) {
    return (grade >= 0.0 && grade <= 100.0);
}

#include "utils.h"
#include <stdio.h>

int backup_file(const char *source_path, const char *backup_path)
{
    FILE *source = fopen(source_path, "r");
    FILE *dest = fopen(backup_path, "w");
    int ch;

    if (source == NULL || dest == NULL) {
        if (source) 
        fclose(source);
        
        if (dest) 
        fclose(dest);
        
        return 0;
    }

    while ((ch = fgetc(source)) != EOF) {
        fputc(ch, dest);
    }

    fclose(source);
    fclose(dest);
    return 1;
}
