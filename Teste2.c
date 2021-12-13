#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define len 10

int main(void) {
  int seed, *arr, count = 0;
  arr = (int *) calloc(len, sizeof(int));

  srand(seed);
  do {
    int num = rand() % n_numbers;
    bool b = false;
    for (int i = 0; i < count; i++) {
      if (arr[i] == num) {
        b = true;
        break;
      }
    }
    if (!b) {
      arr[count] = num;
      count++;
    }
  } while (count < n_numbers);

  return 0;
}