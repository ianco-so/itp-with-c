#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LEN 50

typedef struct PERSON{
    char name[NAME_LEN];
    int age;
    char gender;
} Person;

Person create (char name[NAME_LEN], int age, char gender) {
    Person p;
    strncpy(p.name, name, NAME_LEN);
    p.age = age;
    p.gender = gender;
    //printf("CREATE: %s,%d,%c\n", p.name, p.age, p.gender);
    return p;
}

Person * update (int *n, Person *people, Person p) {
    //printf("UPDATE: %s,%d,%c\n", p.name, p.age, p.gender);
    people = realloc(people, sizeof(Person) * (*n +1));
    strncpy(people[*n].name, p.name, NAME_LEN);
    people[*n].age = p.age;
    people[*n].gender = p.gender;
    //printf("UPDATE: %s,%d,%c\n", people[*n].name, people[*n].age, people[*n].gender);
    *n = *n + 1;
    return people;
}

void print_people(int n, Person *people) {
    for (int i = 0; i < n; i++) {
        printf("%s,%d,%c\n", people[i].name, people[i].age, people[i].gender);
    }
}

Person * delete(int *n, Person *people, Person p) {
    int isEqual = 0;
    int pos = 0;
    //Person *newpeople = NULL;
    for (int i = 0; i < *n; i++) {
        if(strcmp(p.name, people[i].name) == 0 && p.age == people[i].age && p.gender == people[i].gender) {
            isEqual = 1;
            pos = i;
            break;
        }
    } 
    if (isEqual) {
        if (pos == *n-1) *n = *n-1;
        else {
            for (int i = pos; i < *n-1; i++) people[i] = people[i+1];
        }
    } else {
        return people;
    }
}

int main(void) {
    char gender = 'A', name[NAME_LEN], op = 'A';
    int count = 0, age = 0;
    Person *people = NULL, p;
    people = malloc(sizeof(Person)*1);
    //printf("test\n");
    do {
        scanf(" %c", &op);
        getchar();
        switch (op) {
            case 'i':
                fgets(name, NAME_LEN, stdin);
                name[strlen(name) - 1] = '\0';
                scanf("%d", &age);
                getchar();
                scanf(" %c", &gender);
                p = create(name, age, gender);
                people = update(&count, people, p);
                break;
            case 'd':
                fgets(name, NAME_LEN, stdin);
                name[strlen(name) - 1] = '\0';
                scanf("%d", &age);
                getchar();
                scanf(" %c", &gender);
                p = create(name, age, gender);
                people = delete(&count, people, p);
                break;
            case 'P':
                print_people(count, people);
                break;
            default:
            break;
        }
    } while (op != 'P');
    return 0;
}