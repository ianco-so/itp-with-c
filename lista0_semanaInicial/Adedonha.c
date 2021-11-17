#include <stdio.h>

int main (void) {
    int dedos [4] = {0,0,0,0};
    scanf("%i %i %i %i", &dedos[0], &dedos[1], &dedos[2], &dedos[3]);
    int soma = dedos[0]+dedos[1]+dedos[2]+dedos[3];
    if (soma > 26) soma = soma-26;
    if (soma == 0) printf("Ei! Ninguém colocou nada!");
    else    printf("Letra: %c", soma+64);
    return 0;
}