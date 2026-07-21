

#ifndef UTILS_H
#define UTILS_H

void trim_newline(char *str);

void clear_input_buffer(void);

int is_valid_studentid(int id);

int is_valid_name(const char *name);

int is_valid_email(const char *email);

int is_valid_phone(const char *phone);

int is_valid_enrollment_year(int year);

int is_valid_gpa(double gpa);

int is_valid_credits(int credits);

int is_valid_capacity(int capacity);

int is_valid_letter_grade(const char *grade);

int is_valid_numeric_grade(double grade);

int backup_file(const char *source_path, const char *backup_path);




#endif