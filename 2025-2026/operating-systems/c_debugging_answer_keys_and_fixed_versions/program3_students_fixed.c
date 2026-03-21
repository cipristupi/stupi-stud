#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    int grade;
} Student;

Student *create_students(int n);
void load_students(Student *s, int n);
float average_grade(const Student *s, int n);
void show_students(const Student *s, int n);
void free_students(Student *s, int n);

Student *create_students(int n) {
    Student *list = malloc((size_t)n * sizeof(Student));
    if (list == NULL) {
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        list[i].name = malloc(16);
        if (list[i].name == NULL) {
            for (int j = 0; j < i; j++) {
                free(list[j].name);
            }
            free(list);
            return NULL;
        }
        list[i].grade = 0;
    }

    return list;
}

void load_students(Student *s, int n) {
    for (int i = 0; i < n; i++) {
        snprintf(s[i].name, 16, "S%d", i);
        s[i].grade = 10 + i;
    }
}

float average_grade(const Student *s, int n) {
    int total = 0;
    for (int i = 0; i < n; i++) {
        total += s[i].grade;
    }
    return n > 0 ? (float)total / n : 0.0f;
}

void show_students(const Student *s, int n) {
    for (int i = 0; i < n; i++) {
        printf("%s -> %d\n", s[i].name, s[i].grade);
    }
    printf("avg = %.2f\n", average_grade(s, n));
}

void free_students(Student *s, int n) {
    for (int i = 0; i < n; i++) {
        free(s[i].name);
    }
    free(s);
}

int main(void) {
    int count = 3;
    Student *group = create_students(count);
    char *note = malloc(20);

    if (group == NULL || note == NULL) {
        free(note);
        free_students(group, 0);
        return 1;
    }

    strcpy(note, "classroom");
    load_students(group, count);
    show_students(group, count);
    printf("note=%s\n", note);
    printf("done\n");

    free(note);
    free_students(group, count);
    return 0;
}
