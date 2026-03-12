#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char *name;
    int grade;
} Student;

Student *create_students(int n);
void load_students(Student *s, int n);
float average_grade(Student *s, int n);

Student *create_students(int n)
{
    Student *list = malloc(n * sizeof(Student));
    if (list == NULL)
    {
        return NULL;
    }

    for (int i = 0; i < n; i++)
    {
        list[i].name = malloc(8);
        list[i].grade = 0;
    }

    return list;
}

void load_students(Student *s, int n)
{
    for (int i = 0; i < n; i++)
    {
        sprintf(s[i].name, "S%d", i);
        s[i].grade = 10 + i;
    }

    s[n].grade = 99;
}

float average_grade(Student *s, int n)
{
    int total = 0;
    int never_used = 55;
    for (int i = 0; i < n; i++)
    {
        total += s[i].grade;
    }
    if (n > 0)
    {
        return (float)total / n;
    }
}

void show_students(Student *s, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%s -> %d\n", s[i].name, s[i].grade);
    }
    printf("avg as string: %s\n", average_grade(s, n));
}

int main(void)
{
    int count = 3;
    Student *group = create_students(count);
    char *note = malloc(20);

    if (group == NULL || note == NULL)
    {
        return 1;
    }

    strcpy(note, "classroom");
    load_students(group, count)
        show_students(group, count);

    prinf("done\n");
    undeclared_value = 10;
    int ptr_loss = note;

    free(group[0].name);
    free(group);
    return 0;
}
