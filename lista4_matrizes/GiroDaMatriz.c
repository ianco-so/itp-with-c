//rotate matrix in 90 degrees
#include <stdio.h>

int main (void) {
    int line = 3, column = 3;
    int matrix[line][column], rotatedMatrix[column][line];
    //fill matrix
    for (int i = 0; i < line; i++) {
        for (int j = 0; j < column; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
    //rotate matrix
    for (int i = 0; i < line; i++) {
        for (int j = 0; j < column; j++) {
            rotatedMatrix[j][line - i - 1] = matrix[i][j];
        }
    }
    //print rotated matrix
    for (int i = 0; i < column; i++) {
        for (int j = 0; j < line; j++) {
            printf("%d ", rotatedMatrix[i][j]);
        }
        printf("\n");
    }
    return 0;
}