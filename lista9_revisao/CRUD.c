#include <stdio.h>
#include <stdlib.h>

#define NAME_LEN 50


typedef struct PERSON{
    char *name;
    int age;
    char gender;
} Person;

Person create (char * name, int age, char gender);
void update (int *n, Person people[*n], Person p);
int delete (Person *persons, Person p);
void print(int n, Person persons[n]);

int main(void) {
    char option = ' ', gender, *name = NULL;
    int age, *countA = NULL;
    Person *people, person;
    *countA = 0;
    people = calloc(1, sizeof(Person));
    printf("test");
    do {
        scanf("%c", option);
        switch (option) {
            case 'i':
                fgets(name, NAME_LEN, stdin);
                scanf("%d", &age);
                scanf("%c", &gender);
                update(countA, people, create(name, age, gender));
                break;
            case 'd':
                break;
            case 'P':
                print(*countA, people);
                break;
            default:
                break;
        }
    } while (option != 'P');
    return 0;
}

Person create (char * name, int age, char gender) {
    Person p = {name, age, gender};
    return p;
}

void update (int *n, Person *people, Person p) {
    people = realloc(people, sizeof(people) * (*n +1));
    people[*n] = p;
    *n++;
}

void print(int n, Person persons[n]) {
    for (int i = 0; i < n; i++) {
        printf("%s %d %c\n", persons[i].name, persons[i].age, persons[i].gender);
    }
}