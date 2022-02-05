//Loop piramide pega um número impar e faz uma piramide invetida retirando os números da a esqquerda e a direita
#include <stdio.h>
#include <stdlib.h>

int main (void) {
    int n = 0;
    scanf("%d", &n);
    n%2 == 0 ? n++ : n;
    int vec[n];

    for (int i = 0; i < n; i++) {
        vec[i] = i+1;
    }
    for (int i = 0; i < (n+1)/2; i++) { //linha
        for (int j = 0; j < n; j++) { //coluna
            if (vec[j] > 0) {
                printf("%d ", vec[j]);
            } else {
                printf("  ");
            }
        }
        //zerar as bordas do vetor
        vec[i] = 0;
        vec[n-i-1] = 0;
        printf("\n");
    }
    return 0;
}