#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "../src/student.h"
#include "../src/course.h"   
#include "../src/grade.h"    
#include "../src/utils.h"


#include "../src/student.c"
#include "../src/utils.c"
 #include "../src/grade.c" 



Student* create_test_student(int id, const char* name, const char* email, double gpa) {
    Student* new_s = (Student*)malloc(sizeof(Student));
    new_s->id = id;
    strcpy(new_s->name, name);
    strcpy(new_s->surname, "TestSurname"); 
    strcpy(new_s->email, email);
    strcpy(new_s->phone, "555-0000");      
    new_s->enrollment_year = 2023;
    strcpy(new_s->major, "CS");
    new_s->gpa = gpa;
    new_s->next = NULL;
    return new_s;
}



void test_search_functions() {
    Student *head = NULL;

    
    Student *s1 = create_test_student(2023001, "Ali", "ali@uni.edu", 3.5);
    Student *s2 = create_test_student(2023002, "Veli", "veli@uni.edu", 2.8);
    
    
    s2->next = s1; // Head -> s2 -> s1 -> NULL
    head = s2;

    
    Student *found = search_student_byid(head, 2023001);
    assert(found != NULL);
    assert(found->id == 2023001);
    assert(strcmp(found->name, "Ali") == 0);

    
    found = search_student_byid(head, 9999999);
    assert(found == NULL);

    
    found = search_student_byname(head, "Veli");
    assert(found != NULL);
    assert(found->id == 2023002);

    
    found = search_student_byemail(head, "ali@uni.edu");
    assert(found != NULL);
    assert(found->id == 2023001);

    
    free_students(&head);
    printf(" test_search_functions passed\n");
}

void test_delete_operation() {
    Student *head = NULL;

    //  300 -> 200 -> 100
    Student *s1 = create_test_student(2023100, "Can", "can@test.com", 3.0);
    Student *s2 = create_test_student(2023200, "Deniz", "deniz@test.com", 3.2);
    Student *s3 = create_test_student(2023300, "Efe", "efe@test.com", 3.8);

    s1->next = NULL;
    s2->next = s1;
    s3->next = s2;
    head = s3;

    
    head = delete_student(head, 2023200);
    assert(search_student_byid(head, 2023200) == NULL);
    assert(search_student_byid(head, 2023300) != NULL); 
    assert(search_student_byid(head, 2023100) != NULL); 

    
    head = delete_student(head, 2023300);
    assert(search_student_byid(head, 2023300) == NULL);
    assert(head->id == 2023100); 
    
    head = delete_student(head, 2023100);
    assert(head == NULL); 

    printf(" test_delete_operation passed\n");
}

void test_file_io_csv() {
    const char *test_filename = "test_students_temp.csv";
    
   
    FILE *fp = fopen(test_filename, "w");
    assert(fp != NULL);
    
    fprintf(fp, "student_id,first_name,last_name,email,phone,enrollment_year,major,gpa\n");
    fprintf(fp, "2024001,TestName,TestSurname,test@uni.edu,555-1234,2024,CS,3.50\n");
    fprintf(fp, "2024002,TestTwo,SurnameTwo,test2@uni.edu,555-5678,2024,EE,2.90\n");
    fclose(fp);

   
    Student *head = load_students_from_csv(test_filename);
    
    
    assert(head != NULL);
    
    
    Student *s1 = search_student_byid(head, 2024001);
    assert(s1 != NULL);
    assert(strcmp(s1->email, "test@uni.edu") == 0);
    assert(s1->gpa == 3.50);

    Student *s2 = search_student_byid(head, 2024002);
    assert(s2 != NULL);

    
    free_students(&head);
    remove(test_filename); 
    printf(" test_file_io_csv passed\n");
}

void test_validations_integration() {
  
    
    Student *head = NULL;
    Student *s_invalid = (Student*)malloc(sizeof(Student));
    s_invalid->id = 123; // Geçersiz ID (format dışı)
    s_invalid->next = NULL;
    head = s_invalid;

    
    Student *result = search_student_byid(head, 123);
    assert(result == NULL);

    free(s_invalid); // free_students kullanmıyoruz çünkü liste tam oluşmadı
    printf(" test_validations_integration passed\n");
}



int main() {
    // Türkçe karakter desteği (utils.c için)
    setlocale(LC_ALL, "");

    printf("\n========== STUDENT MODULE TESTS ==========\n\n");

    test_search_functions();
    test_delete_operation();
    test_file_io_csv();
    test_validations_integration();

    printf("\n==========================================\n");
    printf("    ALL STUDENT TESTS PASSED SUCCESSFULLY\n");
    printf("==========================================\n");

    return 0;
}