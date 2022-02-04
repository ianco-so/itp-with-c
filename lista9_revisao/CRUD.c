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
    Person *newpeople = NULL;
    for (int i = 0; i < *n; i++) {
        if(strcmp(p.name, people[i].name) == 0 && p.age == people[i].age && p.gender == people[i].gender) {
            isEqual = 1;
            pos = i;
            people[i].name[0] = '\0';
            people[i].age = 0;
            people[i].gender = '\0';
            break;
        }
    } 
    if (isEqual) {
        newpeople = malloc(sizeof(Person*)*(*n-1));
        for(int i = 0; i < pos; i++) {
            strncpy(newpeople[i].name, people[i].name, NAME_LEN);
            newpeople[i].age = people[i].age;
            newpeople[i].gender = people[i].gender;
        }
        for (int i = pos+1; i < *n; i++) {
            strncpy(newpeople[i-1].name, people[i].name, NAME_LEN);
            newpeople[i-1].age = people[i].age;
            newpeople[i-1].gender = people[i].gender;
        }
        *n = *n-1;
        return newpeople;
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
        //getchar();
        switch (op) {
            case 'i':
                getchar();
                fgets(name, NAME_LEN, stdin);
                name[strlen(name) - 1] = '\0';
                scanf("%d", &age);
                getchar();
                scanf(" %c", &gender);
                p = create(name, age, gender);
                people = update(&count, people, p);
                break;
            case 'd':
                getchar();
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