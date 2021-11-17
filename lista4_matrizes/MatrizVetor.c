#include <stdio.h>
//Generate and print a vector whose elements are the sum of the lines of the matrix
int main (void) {
    int line = 3 , column = 5;
    int matrixA[line][column];
    //Fill the matrix
    for (int i = 0; i < line; i++) 
        for (int j = 0; j < column; j++)
            scanf("%d", &matrixA[i][j]);
    //Sum of the lines and print it
    printf("SL = [");
    for (int i = 0; i < line; i++) {
        int sum = 0;
        for (int j = 0; j < column; j++)
            sum += matrixA[i][j];
        i == line-1? printf("%i", sum):printf("%i ", sum);
    }
    printf("]");
    return 0;
}