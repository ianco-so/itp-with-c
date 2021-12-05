#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int diadasemana(char entrada[11], char *saida, int *bissexto) {
    if (entrada[strlen(entrada)-1] ==  '\n') entrada[strlen(entrada)-1] = '\0';
    char *data = strtok(entrada, "/");
    if (data == NULL) return -2;
    int dia = atoi(data);
    data = strtok(NULL, "/");
    if (data == NULL) return -2;
    int mes = atoi(data);
    data = strtok(NULL, "/");
    if (data == NULL) return -2;
    int ano = atoi(data);
    if (dia < 1 || dia > 31) return -1;
    if (mes < 1 || mes > 12) return -1;
    if (ano < 1) return -1;
    // leap year check
    if (ano % 4 == 0) {
        if (ano % 100 == 0) {
            if (ano % 400 == 0) *bissexto = 1;
            else  *bissexto = 0;
        } else  *bissexto = 1;
    } else *bissexto = 0;

    //check if date is valid
    if ((mes == 4 || mes == 6 || mes == 9 || mes == 11) && dia > 30) return -1;
    else if (mes == 2) {
        if (*bissexto == 1) {
            if (dia > 29) return -1;
        } else if (dia > 28) return -1;
    }
    int diasemana = (23*mes/9+dia+4+(mes<3?ano--:ano-2)+ano/4-ano/100+ano/400)%7;
    switch (diasemana) {
        case 0:
           strcpy(saida, "Domingo\0");
            break;
        case 1: 
            strcpy(saida, "Segunda\0");
            break;
        case 2: 
            strcpy(saida, "Terça\0");
            break;
        case 3: 
            strcpy(saida, "Quarta\0");
            break;
        case 4: 
            strcpy(saida, "Quinta\0");
            break;
        case 5: 
            strcpy(saida, "Sexta\0");
            break;
        case 6: 
            strcpy(saida, "Sabado\0");
            break;
        default:
            return -1;
    }
    return 1;
}

int main(void) {
    int status = 0, bissexto = 0;
    char entrada[11] = {0}, *saida = NULL;
    fgets(entrada, 11, stdin);
    saida = (char *) calloc(10, sizeof(char));
    status = diadasemana(entrada, saida, &bissexto);
    if (status>0)   printf("%s.%s\n", saida, bissexto? " Ano bissexto." : "");
    else {
        if (status == -1)   printf("Data inexistente.\n");
        else    printf("Entrada invalida.\n");
        return 1;
    }
    return 0;
}