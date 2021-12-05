#include <stdio.h>
#include <stdlib.h>

int * read_vector(int *n) {
    int *v;
    int len = 1;
    
    v = malloc(sizeof(int));
    do {
        scanf("%d", &v[len-1]);
        v = realloc(v, sizeof(int) * (len + 1));
        len++;
    } while (getchar() != '\n');
    len--;
    *n = len;

    return v;
}

int main (void) {
    int *V1, *V2;
    int V1_length = 1, V2_length = 1;

    V1 = read_vector(&V1_length);
    V2 = read_vector(&V2_length);

    if (V1_length == V2_length) for (int i = 0; i < V1_length; i++) printf("%d ", V1[i] + V2[i]);
    else  printf("Vetores de tamanhos diferentes!");

    free(V1);
    free(V2);
    return 0;
}