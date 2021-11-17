#include <stdio.h>
//find the line of the matrix whose have the highest last element and that has a third valid element
int main (void) {
    int line = 5, column = 4, class = 0, max = -1;
    int matrix[line][column];
    //fill the matrix
    for (int i = 0; i < line; i++)
        for (int j = 0; j < column; j++)
            scanf("%d", &matrix[i][j]);
    scanf("%d", &class);
    for (int i = 0; i < line; i++)
        if (matrix[i][2] == class)
            if (matrix[i][4] > max)
                max = matrix[i][3];
    if (max == -1)
        printf("Curso nao existente");
    else
        for (int i = 0; i < line; i++)
            if (matrix[i][3] == max)
                printf("CR = %i\nMatricula = %i", matrix[i][3], matrix[i][0]);
    return 0;
}