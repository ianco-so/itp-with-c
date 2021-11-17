#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
  int dice, turns;

  printf("What kind of dice you have? ");
  scanf("%d", &dice);
  printf("How many turns? ");
  scanf("%d", &turns);

  //sreend give a seed to the random generator and time(NULL) gives the current time to seed the generator
  srand(time(NULL));
  for(int i=0; i<turns; i++)  printf("Turn %d: %d\n", i+1, rand()%dice + 1);
  printf("\n");

  return 0;
}