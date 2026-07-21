#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "professor.h"

void add_professor(Professor **head) {
    Professor *newProf = (Professor *)malloc(sizeof(Professor));

    if (newProf == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    printf("Professor ID: ");
    scanf("%d", &newProf->professor_id);

    printf("First name: ");
    scanf("%s", newProf->first_name);

    printf("Last name: ");
    scanf("%s", newProf->last_name);

    printf("Email: ");
    scanf("%s", newProf->email);

    printf("Phone: ");
    scanf("%s", newProf->phone);

    printf("Department: ");
    scanf("%s", newProf->department);

    printf("Title: ");
    scanf("%s", newProf->title);

    printf("Office: ");
    scanf("%s", newProf->office);

    newProf->next = *head;
    *head = newProf;

    printf("Professor added successfully.\n");
}
void edit_professor(Professor *head) {
    int id;
    printf("Enter Professor ID to edit: ");
    scanf("%d", &id);

    Professor *prof = search_professor(head, id);

    if (prof == NULL) {
        printf("Professor not found.\n");
        return;
    }

    printf("New email: ");
    scanf("%s", prof->email);

    printf("New phone: ");
    scanf("%s", prof->phone);

    printf("New department: ");
    scanf("%s", prof->department);

    printf("New title: ");
    scanf("%s", prof->title);

    printf("New office: ");
    scanf("%s", prof->office);

    printf("Professor information updated.\n");
}
void delete_professor(Professor **head) {
    int id;
    printf("Enter Professor ID to delete: ");
    scanf("%d", &id);

    Professor *temp = *head;
    Professor *prev = NULL;

    while (temp != NULL && temp->professor_id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Professor not found.\n");
        return;
    }

    if (prev == NULL) {
        *head = temp->next;   
    } else {
        prev->next = temp->next;
    }

    free(temp);
    printf("Professor deleted successfully.\n");
}

Professor* search_professor(Professor *head, int professor_id) {
    while (head != NULL) {
        if (head->professor_id == professor_id) {
            return head;   
        }
        head = head->next;
    }
    return NULL;  
}

void display_professor(Professor *head) {
    if (head == NULL) {
        printf("No professors to display.\n");
        return;
    }

    while (head != NULL) {
        printf("\nID: %d\n", head->professor_id);
        printf("Name: %s %s\n", head->first_name, head->last_name);
        printf("Email: %s\n", head->email);
        printf("Phone: %s\n", head->phone);
        printf("Department: %s\n", head->department);
        printf("Title: %s\n", head->title);
        printf("Office: %s\n", head->office);
        printf("-------------------------\n");

        head = head->next;
    }
}

void assign_professor_to_course(Professor *pHead, Course *cHead) {
    int pid, cid;
    
    printf("Enter Professor ID: ");
    scanf("%d", &pid);
    
    Professor *prof = search_professor(pHead, pid);
    if (!prof) {
        printf("Professor not found.\n");
        return;
    }
    
    printf("Enter Course ID: ");
    scanf("%d", &cid);
    
    Course *course = search_course_byid(cHead, cid);
    if (!course) {
        printf("Course not found.\n");
        return;
    }
    
    course->professor_id = pid;
    printf("Professor %s %s assigned to course %s (%s).\n",  prof->first_name, prof->last_name, course->course_name, course->course_code);
}

void free_professors(Professor **head) {
    Professor *current = *head;
    Professor *temp;

    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }
    *head = NULL;
}

Professor* load_professors_from_csv(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (!fp)
    {
        printf("Error: professors.csv could not be opened.\n");
        return NULL;
    }

    Professor *head = NULL;
    char line[512];
    int count = 0;  

    fgets(line, sizeof(line), fp); 

    while (fgets(line, sizeof(line), fp))
    {
        Professor *p = malloc(sizeof(Professor));
        if (!p)
            break;

        p->next = NULL; 

        int fields = sscanf(
            line,
            "%d,%9[^,],%49[^,],%99[^,],%19[^,],%29[^,],%19[^,],%9[^,\n]",
            &p->professor_id,
            p->first_name,
            p->last_name,
            p->email,
            p->phone,
            p->department,
            p->title,
            p->office
        );

        if (fields != 8)
        {
            free(p);
            continue;
        }

        p->next = head;
        head = p;

        count++; // (example: 30professor loaded)
    }

    fclose(fp);

    printf("%d professors loaded successfully.\n", count); 
    return head;
}


void save_professors_to_csv(const char *filename, Professor *head) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        printf("File could not be opened for writing.\n");
        return;
    }

    fprintf(fp, "professor_id,first_name,last_name,email,phone,department,title,office\n");

    while (head) {
        fprintf(fp, "%d,%s,%s,%s,%s,%s,%s,%s\n",
                head->professor_id,
                head->first_name,
                head->last_name,
                head->email,
                head->phone,
                head->department,
                head->title,
                head->office);
        head = head->next;
    }

    fclose(fp);
}

