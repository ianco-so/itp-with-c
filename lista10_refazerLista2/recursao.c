#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// metodo recursivo para calcular a quantidade de vezes que K aparece em N
int conta_digitos(int N, int K) {
    if (N < 10) {
        if (N == K) {
            return 1;
        } else {
            return 0;
        }
    } else {
        if (N % 10 == K) {
            return 1 + conta_digitos(N / 10, K);
        } else {
            return conta_digitos(N / 10, K);
        }
    }
    //return 1 + conta_digitos(N/K, K);
}

int main (void) {
    int N = 0; //Numero natural N
    int K = 0; //digito K
    int i = 0; //contador (quantas vezes K aparece em N)

    scanf("%d", &N);
    getchar();
    scanf("%d", &K);
    getchar();

    i = conta_digitos(N, K);

    printf("O digito %d aparece %d vezes no numero %d\n", K, i, N);
    return 0;
}