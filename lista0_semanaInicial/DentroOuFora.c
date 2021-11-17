#include <stdio.h>

int main (void) {
    int A[2], B[2], C[2];
    scanf("%i %i %i %i ", &A[0], &A[1], &B[0], &B[1]);
    scanf("%i %i", &C[0], &C[1]);
    if (C[0] >= A[0] && C[0] <= B[0] && C[1] >= A[1] && C[1] <= B[1])   printf("Dentro!");
    else  printf("Fora!");
    return 0;
}