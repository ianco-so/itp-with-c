#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int nlin, ncol;
    int **mat;
} Matrix;

Matrix* createMatrix(int nlin, int ncol);
void readMatrix(Matrix *m);
void printMatrix(Matrix *m);
void destroyMatrix(Matrix **m);

int main(void) {
    int lin, col;
    Matrix* mat;
    scanf("%i %i", &lin, &col);
    mat = createMatrix(lin, col);
    readMatrix(mat);
    printMatrix(mat);
    destroyMatrix(&mat);
    if (mat == NULL) {
        printf("OK\n");
    }
    return 0;
}

Matrix * createMatrix (int nlin, int ncol) {
    Matrix *m = (Matrix *) calloc(1, sizeof(Matrix));
    m->nlin = nlin;
    m->ncol = ncol;
    m->mat = (int **) calloc(nlin, sizeof(int *));
    for (int i = 0; i < nlin; i++) {
        m->mat[i] = (int *) calloc(ncol, sizeof(int));
    }
    return m;
}

void readMatrix(Matrix *m) {
    for (int i = 0; i < m->nlin; i++) {
        for (int j = 0; j < m->ncol; j++) {
            scanf("%i", &m->mat[i][j]);
        }
    }
}

void printMatrix(Matrix *m) {
    for (int i = 0; i < m->nlin; i++) {
        for (int j = 0; j < m->ncol; j++) printf("%i ", m->mat[i][j]);
        printf("\n");
    }
}

void destroyMatrix(Matrix **m) {
    for (int i = 0; i < (*m)->nlin; i++) {
        free((*m)->mat[i]);
    }
    free((*m)->mat);
    free(*m);
    *m = NULL;
}