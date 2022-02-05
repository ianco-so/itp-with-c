#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// estrutura da turma
typedef struct TURMA {
    int matricula;
    char nome[50];
    int faltas;
    char status[10];
} Turma;

Turma simula_entrada (int i) {
    Turma turma;

    switch (i) {
        case 0:
            turma.matricula = 202254101;
            strcpy(turma.nome, "Joao");
            turma.faltas = 0;
            strcpy(turma.status, "aprovado");
            break;
        case 1:
            turma.matricula = 202254102;
            strcpy(turma.nome, "Maria");
            turma.faltas = 0;
            strcpy(turma.status, "reprovado");
            break;
        case 2:
            turma.matricula = 202254103;
            strcpy(turma.nome, "Jose");
            turma.faltas = 0;
            strcpy(turma.status, "aprovado");
            break;
        case 3:
            turma.matricula = 202254104;
            strcpy(turma.nome, "Ana");
            turma.faltas = 10;
            strcpy(turma.status, "reprovado");
            break;
        case 4:
            turma.matricula = 202254105;
            strcpy(turma.nome, "Pedro");
            turma.faltas = 20;
            strcpy(turma.status, "aprovado");
            break;
        case 5:
            turma.matricula = 202254106;
            strcpy(turma.nome, "Tiago");
            turma.faltas = 25;
            strcpy(turma.status, "reprovado");
            break;
        case 6:
            turma.matricula = 202254107;
            strcpy(turma.nome, "Jorge");
            turma.faltas = 03;
            strcpy(turma.status, "aprovado");
            break;
        case 7:
            turma.matricula = 202254108;
            strcpy(turma.nome, "Joana");
            turma.faltas = 07;
            strcpy(turma.status, "aprovado");
            break;
        case 8:
            turma.matricula = 202254109;
            strcpy(turma.nome, "Paulo");
            turma.faltas = 30;
            strcpy(turma.status, "reprovado");
            break;
        case 9:
            turma.matricula = 202254110;
            strcpy(turma.nome, "Sintia");
            turma.faltas = 70;
            strcpy(turma.status, "reprovado");
            break;
        default:
            break;
    }
    return turma;
}

void listaTurma(Turma *turma, int i) {
    //printf("Matricula: %d\n", turma[i].matricula);
    //printf("Nome: %s\n", turma[i].nome);
    //printf("Faltas: %d\n", turma[i].faltas);
    //printf("Status: %s\n", turma[i].status);
}

int main(void) {
    Turma *turma;
    turma = (Turma *) malloc(sizeof(Turma));
    for (int i = 0; i < 10; i++) {
        turma = (Turma *) realloc(turma, (i + 1) * sizeof(Turma));
        turma[i] = simula_entrada(i);
    }
    for (int i = 0; i < 10; i++) {
        listaTurma(turma, i);
        //printf("\n");
    }	
    return 0;
}