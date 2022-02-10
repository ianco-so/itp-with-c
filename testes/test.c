#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define MAX_STR 50

void readData(int h, int w, int matriz[h][w], int meuBot[], int porto[], int matrizBots[h][w], char myId[MAX_STR]) {
    int n;
    int ponto;
    char id[MAX_STR];
    int res, x = 0, y = 0;

    for (int i = 0; i < h; i++) {  
        for (int j = 0; j < w; j++) {
            scanf("%i", &(matriz[i][j]));
            (matrizBots[i][j]) = 0;
            if (matriz[i][j] == 1){
                porto[0] = i;
                porto[1] = j;
            }
        }
    }

    scanf(" BOTS %i", &n);

    for (int i = 0; i < n; i++) {
        scanf("%s %i %i", id, &x, &y);
        res = strcmp(id, myId);
        if(res == 0){
            (meuBot[0]) = x;
            (meuBot[1]) = y;
        } else {
            (matrizBots[x][y]) = 1;
        }
    }
}

int main(){
    int linha, coluna;
    int estoque = 0;
    char myId[MAX_STR];
    char resultado_acao[MAX_STR];

    setbuf(stdin, NULL);   // stdin, stdout e stderr não terão buffers
    setbuf(stdout, NULL);  // assim, nada é "guardado temporariamente"
    setbuf(stderr, NULL);

    scanf("AREA %i %i", &linha, &coluna);

    int matriz[linha][coluna];
    int matrizBots[linha][coluna];
    int meuBot[2];
    int porto[2];
   

    scanf(" ID %s", myId);
    srand( (unsigned)time(NULL) );

    while (1){

        readData(linha, coluna, matriz, meuBot, porto, matrizBots, myId);

        int posicao_linha = meuBot[0];
        int posicao_coluna = meuBot[1];
        int loc_bot = matriz[posicao_linha][posicao_coluna];
        int aleatorio = 1 + ( rand() % 4 );

        // SE O BOT ESTIVER ENCIMA DO PORTO ELE JÁ VENDE OS PEIXES DISPONIVEIS
        if (loc_bot == 1 && estoque > 0){
            printf("SELL\n");
            estoque = 0;
        }
        // VERIFICA SE EXISTE PEIXES QUE PODEM SER PESCADOS E SE O ESTOQUE É MENOR QUE 10 E A QUANTIDADE DE PEIXES MAIOR QUE 1
        else if ((loc_bot > 11 && loc_bot < 20 && estoque < 10) || (loc_bot > 21 && loc_bot < 30 && estoque < 10) || (loc_bot > 31 && loc_bot < 40 && estoque < 10)){
            printf("FISH\n");
            estoque = estoque + 1;
        }

        // BOT PROCURA O PORTO PARA PODER VENDER
        else if (estoque == 10){
            if (posicao_linha > porto[0]){
                printf("UP\n");
            }
            else if (posicao_linha < porto[0]){
                printf("DOWN\n");
            }
            else if (posicao_coluna < porto[1]){
                printf("RIGHT\n");
            }
            else if (posicao_coluna > porto[1]){
                printf("LEFT\n");
            }
        }
        // VERIFICA SE EXISTE UM PONTO DE PESCA DE ROBALO AO REDOR E ENTÃO VAI ATÉ ELE (R$200,00)
        else if (posicao_coluna - 1 > 0 && matriz[posicao_linha][posicao_coluna-1] > 31 && matriz[posicao_linha][posicao_coluna-1] < 40 && matrizBots[posicao_linha][posicao_coluna-1] != 1){
            printf("LEFT\n");
        }
        else if (posicao_coluna + 1 < coluna && matriz[posicao_linha][posicao_coluna+1] > 31 && matriz[posicao_linha][posicao_coluna+1] < 40 && matrizBots[posicao_linha][posicao_coluna+1] != 1){
            printf("RIGHT\n");
        }
        else if (posicao_linha - 1 > 0 && matriz[posicao_linha-1][posicao_coluna] > 31 && matriz[posicao_linha][posicao_coluna] < 40 && matrizBots[posicao_linha-1][posicao_coluna] != 1){
            printf("UP\n");
        }
        else if (posicao_linha + 1 < linha && matriz[posicao_linha+1][posicao_coluna] > 31 && matriz[posicao_linha][posicao_coluna] < 40 && matrizBots[posicao_linha+1][posicao_coluna] != 1){
            printf("DOWN\n");
        }

        // VERIFICA SE EXISTE UM PONTO DE PESCA DE CIOBA AO REDOR E ENTÃO VAI ATÉ ELE (R$150,00)
        else if (posicao_coluna - 1 > 0 &&matriz[posicao_linha][posicao_coluna-1] > 21 && matriz[posicao_linha][posicao_coluna-1] < 30 && matrizBots[posicao_linha][posicao_coluna-1] != 1){
            printf("LEFT\n");
        }
        else if (posicao_coluna + 1 < coluna && matriz[posicao_linha][posicao_coluna+1] > 21 && matriz[posicao_linha][posicao_coluna+1] < 30 && matrizBots[posicao_linha][posicao_coluna+1] != 1){
            printf("RIGHT\n");
        }
        else if (posicao_linha - 1 > 0 && matriz[posicao_linha-1][posicao_coluna] > 21 && matriz[posicao_linha-1][posicao_coluna] < 30 && matrizBots[posicao_linha-1][posicao_coluna] != 1){
            printf("UP\n");
        }
        else if (posicao_linha + 1 < linha && matriz[posicao_linha+1][posicao_coluna] > 21 && matriz[posicao_linha+1][posicao_coluna] < 30 && matrizBots[posicao_linha+1][posicao_coluna] != 1){
            printf("DOWN\n");
        }

        // VERIFICA SE EXISTE UM PONTO DE PESCA DE TAINHA AO REDOR E ENTÃO VAI ATÉ ELE (R$100,00)
        else if (posicao_coluna - 1 > 0 && matriz[posicao_linha][posicao_coluna-1] > 11 && matriz[posicao_linha][posicao_coluna-1] < 20 && matrizBots[posicao_linha][posicao_coluna-1] != 1){
            printf("LEFT\n");
        }
        else if (posicao_coluna + 1 < coluna &&  matriz[posicao_linha][posicao_coluna+1] > 11 && matriz[posicao_linha][posicao_coluna+1] < 20 && matrizBots[posicao_linha][posicao_coluna+1] != 1){
            printf("RIGHT\n");
        }
        else if (posicao_linha - 1 > 0 && matriz[posicao_linha-1][posicao_coluna] > 11 && matriz[posicao_linha-1][posicao_coluna] < 20 && matrizBots[posicao_linha-1][posicao_coluna] != 1){
            printf("UP\n");
        }
        else if (posicao_linha + 1 < linha && matriz[posicao_linha+1][posicao_coluna] > 11 && matriz[posicao_linha+1][posicao_coluna] < 20 && matrizBots[posicao_linha+1][posicao_coluna] != 1){
            printf("DOWN\n");
        }
       
        // CASO NÃO EXISTE PEIXE AO REDOR, ELE ENTÃO VAI ATÉ UM PONTO ALEATORIO (DEFINIDO PELA VARIAVEL "aleatorio")
        else if (posicao_coluna - 1 > 0 && aleatorio == 0 && matrizBots[posicao_linha][posicao_coluna-1] != 1){
            printf("LEFT\n");
        }
        else if (posicao_coluna + 1 < coluna && aleatorio == 1 && matrizBots[posicao_linha][posicao_coluna+1] != 1){
            printf("RIGHT\n");
        }
        else if (posicao_linha - 1 > 0 && aleatorio == 2 && matriz[posicao_linha-1][posicao_coluna] != 1){
            printf("UP\n");
        }
        else if (posicao_linha + 1 < linha && aleatorio == 3 && matrizBots[posicao_linha+1][posicao_coluna] != 1){
            printf("DOWN\n");
        }

        // POR FIM CASO ALGUMA DESSAS POSIÇÕES ESTEJA OCUPADA ELE TENTA IR PARA UMA AS POSIÇÕES SEGUINDO A ORDEM ABAIXO
        else{
            if (posicao_coluna - 1 > 0 && matrizBots[posicao_linha][posicao_coluna-1] != 1){


                printf("LEFT\n");
            }
            else if (posicao_linha - 1 > 0 && matriz[posicao_linha+1][posicao_coluna] != 1){
                printf("UP\n");
            }
            else if (posicao_coluna + 1 < coluna && matriz[posicao_linha][posicao_coluna+1] != 1){
                printf("RIGHT\n");
            }
            else if (posicao_linha + 1 < linha){
                printf("DOWN\n");
            }
        }

        // LÊ O RESULTADO DA AÇÃO, ENVIADO PELO OCMA.
        scanf("%s", resultado_acao);
    }
    return 0;
}