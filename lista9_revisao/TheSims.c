#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define str_len 20

int simula_sims(int *fome, int *sede, int *banheiro, int *sono, int *tedio) {
    char str[str_len];
    fgets(str, str_len, stdin);
    str[strlen(str) - 1] = '\0';

    if (strcmp(str, "comer") == 0) {
        *fome = *fome + 30 >= 100 ? 100 : *fome + 30;
        *banheiro = *banheiro - 15 <= 0 ? 0 : *banheiro - 15;
        *sono = *sono - 5 <= 0 ? 0 : *sono - 5;
        *tedio = *tedio - 5 <= 0 ? 0 : *tedio - 5;
        *sede = *sede - 5 <= 0 ? 0 : *sede - 5;
    } else if (strcmp(str, "beber") == 0) {
        *sede = *sede + 30 >= 100 ? 100 : *sede + 30;
        *banheiro = *banheiro - 20 <= 0 ? 0 : *banheiro - 20;
        *sono = *sono - 5 <= 0 ? 0 : *sono - 5;
        *tedio = *tedio - 5 <= 0 ? 0 : *tedio - 5;
        *fome = *fome - 5 <= 0 ? 0 : *fome - 5;
    } else if (strcmp(str, "dormir") == 0) {
        *sono = *sono + 80 >= 100 ? 100 : *sono + 80;
        *fome = *fome - 30 <= 0 ? 0 : *fome - 30;
        *sede = *sede - 30 <= 0 ? 0 : *sede - 30;
        *banheiro = *banheiro - 30 <= 0 ? 0 : *banheiro - 30;
        *tedio = *tedio + 30 >= 100 ? 100 : *tedio + 30;
    } else if (strcmp(str, "se aliviar") == 0) {
        *banheiro = 100;
        *sono = *sono - 5 <= 0 ? 0 : *sono - 5;
        *tedio = *tedio - 5 <= 0 ? 0 : *tedio - 5;
        *fome = *fome - 5 <= 0 ? 0 : *fome - 5;
        *sede = *sede - 5 <= 0 ? 0 : *sede - 5;
    } else if (strcmp(str, "jogar videogame") == 0) {
        *tedio = *tedio + 80 >= 100 ? 100 : *tedio + 80;
        *fome = *fome - 20 <= 0 ? 0 : *fome - 20;
        *sede = *sede - 20 <= 0 ? 0 : *sede - 20;
        *banheiro = *banheiro - 20 <= 0 ? 0 : *banheiro - 20;
        *sono = *sono - 20 <= 0 ? 0 : *sono - 20;
    }

    if (*fome <= 0 || *sede <= 0 || *banheiro <= 0 || *sono <= 0 || *tedio <= 0) {
        printf("Game Over! ");
        if (*fome <= 0) printf("Morreu de fome\n");
        else if (*sede <= 0) printf("Morreu de sede\n");
        else if (*banheiro <= 0) printf("Morreu apertado...\n");
        else if (*sono <= 0) printf("Morreu de sono\n");
        else if (*tedio <= 0) printf("Morreu de tédio\n");
        return 0;
    } else {
        if(*fome <= 15) printf("Alerta: fome está com valor baixo\n");
        if(*sede <= 15) printf("Alerta: sede está com valor baixo\n");
        if(*banheiro <= 15) printf("Alerta: banheiro está com valor baixo\n");
        if(*sono <= 15) printf("Alerta: sono está com valor baixo\n");
        if(*tedio <= 15) printf("Alerta: tédio está com valor baixo\n");
        return 1;
    }
}

void imprime_relatorio(int fome, int sede, int banheiro, int sono, int tedio) {
    printf("Status final:\n");
    printf("Fome: %d\n", fome);
    printf("Sede: %d\n", sede);
    printf("Banheiro: %d\n", banheiro);
    printf("Sono: %d\n", sono);
    printf("Tédio: %d\n", tedio);
}

int main (void) {
    int fome, sede, banheiro, sono, tedio;
    int acoes;

    scanf("%d %d %d %d %d", &fome, &sede, &banheiro, &sono, &tedio);
    scanf("%d", &acoes);
    getchar();
    for(int i = 0; i<acoes; i++){
        int ret = simula_sims(&fome, &sede, &banheiro, &sono, &tedio);
        if(ret == 0) break;
    }

    imprime_relatorio(fome, sede, banheiro, sono, tedio);

    return 0;
}