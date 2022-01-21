#include <stdio.h>
#include <math.h>

//find the extreme values of each column of the matrix with regression
void find_values(int row, int col, int mat[row][col], int i, int j, int min, int max) {
    if (j < col) {
        if (i < row) {
            if (mat[i][j] > max) {
                max = mat[i][j];
            }
            if (mat[i][j] < min) {
                min= mat[i][j];
            }
            find_values(row, col, mat, i + 1, j, min, max);
        } else {
            printf("Munucipio %d: %d %d\n",j+1, min, max);
            find_values(row, col, mat, 0, j + 1, 1000000, 0);
        }
    } else {
        return;
    }
}

int main(void){          
    int col, row;
    scanf("%d %d", &row, &col);
    int mat [row][col];
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            scanf("%d", &(mat[i][j]));
        }
    }
    find_values(row, col, mat, 0, 0, 99999999, 0);
    return 0;
}