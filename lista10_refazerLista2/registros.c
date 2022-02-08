#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// estrutura da turma
typedef struct ESTUDANTE {
    int matricula;
    char nome[10];
    int faltas;
    double media;
    char situacao[10];
} Aluno;

void simula_entrada (int i, Aluno *turma) {
    switch (i) {
        case 0:
            turma[i].matricula = 123;
            strcpy(turma[i].nome, "josé");
            turma[i].faltas = 10;
            turma[i].media = 9.0;
            strcpy(turma[i].situacao, "aprovado");
            break;
        case 1:
            turma[i].matricula = 133;
            strcpy(turma[i].nome, "Maria");
            turma[i].faltas = 90;
            turma[i].media = 3.0;
            strcpy(turma[i].situacao, "reprovado");
            break;
        case 2:
            turma[i].matricula = 202254103;
            strcpy(turma[i].nome, "Jose");
            turma[i].faltas = 0;
            strcpy(turma[i].situacao, "aprovado");
            break;
        case 3:
            turma[i].matricula = 202254104;
            strcpy(turma[i].nome, "Ana");
            turma[i].faltas = 10;
            turma[i].media = 4.5;
            strcpy(turma[i].situacao, "reprovado");
            break;
        case 4:
            turma[i].matricula = 202254105;
            strcpy(turma[i].nome, "Pedro");
            turma[i].faltas = 20;
            turma[i].media = 7.5;
            strcpy(turma[i].situacao, "aprovado");
            break;
        case 5:
            turma[i].matricula = 202254106;
            strcpy(turma[i].nome, "Tiago");
            turma[i].faltas = 25;
            turma[i].media = 8.0;
            strcpy(turma[i].situacao, "aprovado");
            break;
        default:
            break;
    }
}



void listaTurma(int nAlunos, Aluno turma[nAlunos]) {
    for (int i = 0; i < nAlunos; i++) {
        printf("%d , %s, %d%%, %.1f, %s\n", turma[i].matricula, turma[i].nome, turma[i].faltas, turma[i].media, turma[i].situacao);
    }
}

int main(void) {
    Aluno turma[10];
    int nTurma = 0;
    scanf("Numero da turma: %d", &nTurma);
    getchar();

    for (int i = 0; i < 2; i++) {
        simula_entrada(i, turma);
    }

    listaTurma(2, turma);

    return 0;
}