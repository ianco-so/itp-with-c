//print suggestions for queries
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 100
#define MAX_TEXT 101  // MAX_TEXT = SIZE + 1

void print_suggestions(char *str, char database[][MAX_TEXT], int n){
    int n_suggestions = 0;
    for (int i = 0; i < n; i++){
      if (strncmp(str, database[i], strlen(str)-1) == 0){
        printf("Do you mean: %s?\n", database[i]);
        n_suggestions++;
      }
    }
    if (n_suggestions == 0) printf ("No suggestions\n");
}

void fill_database(int i, char database[][MAX_TEXT]) {
  fgets(database[i], MAX_TEXT, stdin);
  database[i][strlen(database[i]) - 1] = '\0';
}

int main(void) {
  char database[SIZE][MAX_TEXT] = {0};
  char str[MAX_TEXT] = {0};
  int previous, current;

  scanf("%d\n", &previous);

  for (int i = 0; i < previous; i++)
    fill_database(i, database);
  scanf("%d\n", &current);
  for (int i = 0; i < current; i++) {
    fgets(str, MAX_TEXT, stdin);
    print_suggestions(str, database, previous);
    printf("\n");
  }
  return 0;
}