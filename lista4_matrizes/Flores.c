//calculete diferences, if exist, between the secund and thrid columns of the matrix
#include <stdio.h>
#include <stdbool.h>

int main (void) {
    int line = 5, column = 3;
    int matrix[line][column];
    bool fullstock = true;
    //fill the matrix
    for (int i = 0; i < line; i++)
        for (int j = 0; j < column; j++)
            scanf("%d", &matrix[i][j]);

    //calculate the differences
    for (int i = 0; i < line; i++)
        if (matrix[i][1] - matrix[i][2] > 0) {
            printf("%d %d\n", matrix[i][0], matrix[i][1] - matrix[i][2]);
            fullstock = false;
        }
    if (fullstock)
        printf("Estoque Completo");
    return 0;
}