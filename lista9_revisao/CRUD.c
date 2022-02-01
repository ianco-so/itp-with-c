#include <stdio.h>
#include <stdlib.h>

define NAME_LEN 50


typedef struct PERSON{
    char *name;
    int age;
    char gender;
} Person;

Person create (char * name, int age, char gender);
void update (int *n, Person *people[p], Person p);
int delete (Person *persons, Person p);
void print(Person *persons);

int main (void) {
    char option = '\0', gender, *name;
    int age, *countA;
    Person *people, person;

    *countA = 0;

    do {
        scanf("%c", option);
        switch (option) {
            case 'i':
                fgets(name, NAME_LEN, stdin);
                scanf("%d", &age);
                scanf("%c", &gender);
                update(&countA, people, create(name, age, gender););
                break;
            case 'd':

                break;
            case 'i':
                break;
            case 'p':
                break;
            default:
                break;
        }
    } while (option !- 'P');
    return 0;
}

Person create (char * name, int age, char gender) {
    Person p = {name, age, gender};
    return p;
}

void update (int *n, Person *people, Person p) {
    people = realloc()
}