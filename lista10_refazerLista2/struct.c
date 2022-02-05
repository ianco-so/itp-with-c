//Ler os dados de, até 10 alunos e depois calcula e mostra a média de cada um.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct DISCIPLINA {
    char codigo [8];
    double nota1;
    double nota2;
} Materia;

typedef struct ESTUDANTE{
    char nome[50];
    int matricula;
    Materia materia;
}Aluno;

Aluno simula_entrada (int i) {
    Turma turma;
    //char * nome = (char *) malloc(sizeof(char) * 50);

    //simulando até 10 entradas de alunos

    switch (i) {
        case 0:
            strcpy(aluno.nome, "Joao");
            aluno.matricula = 202254101;
            strcpy(aluno.materia.codigo,"IMD0021");
            aluno.materia.nota1 = 10.0;
            aluno.materia.nota2 = 8.0;
            break;
        case 1:
            strcpy(aluno.nome,"Maria");
            aluno.matricula = 202254102;
            strcpy(aluno.materia.codigo, "IMD0022");
            aluno.materia.nota1 = 5.5;
            aluno.materia.nota2 = 6.7;
            break;
        case 2:
            strcpy(aluno.nome,"Jose");
            aluno.matricula = 202254103;
            strcpy(aluno.materia.codigo, "IMD0023");
            aluno.materia.nota1 = 9.0;
            aluno.materia.nota2 = 7.4;
            break;
        case 3:
            strcpy(aluno.nome, "Ana");
            aluno.matricula = 202254104;
            strcpy(aluno.materia.codigo, "IMD0024");
            aluno.materia.nota1 = 4.5;
            aluno.materia.nota2 = 8.9;
            break;
        case 4:
            strcpy(aluno.nome, "Pedro");
            aluno.matricula = 202254105;
            strcpy(aluno.materia.codigo, "IMD0025");
            aluno.materia.nota1 = 0.2;
            aluno.materia.nota2 = 3.4;
            break;
        case 5:
            strcpy(aluno.nome, "Joana");
            aluno.matricula = 202254106;
            strcpy(aluno.materia.codigo, "IMD0026");
            aluno.materia.nota1 = 10.0;
            aluno.materia.nota2 = 10.0;
            break;
        case 6:
            strcpy(aluno.nome, "Paulo");
            aluno.matricula = 202254107;
            strcpy(aluno.materia.codigo, "IMD0027");
            aluno.materia.nota1 = 7.1;
            aluno.materia.nota2 = 3.4;
            break;
        case 7:
            strcpy(aluno.nome, "Jorge");
            aluno.matricula = 202254108;
            strcpy(aluno.materia.codigo, "IMD0028");
            aluno.materia.nota1 = 4.9;
            aluno.materia.nota2 = 8.9;
            break;
        case 8:
            strcpy(aluno.nome, "Matheus");
            aluno.matricula = 202254109;
            strcpy(aluno.materia.codigo, "IMD0029");
            aluno.materia.nota1 = 10.0;
            aluno.materia.nota2 = 5.0;
            break;
        case 9:
            strcpy(aluno.nome, "Lucas");
            aluno.matricula = 202254110;
            strcpy(aluno.materia.codigo, "IMD0030");
            aluno.materia.nota1 = 9.0;
            aluno.materia.nota2 = 7.4;
            break;
        default:
            break;
    }
    return turma;
}

int main (void) {
    int nAlunos = 7;
    //scanf("%d", &nAlunos);
    Aluno alunos[nAlunos];

    for (int i = 0; i < nAlunos; i++) {
        alunos[i] = simula_entrada(i);
    }

    //calculando e exibindo a media ponderada de cada aluno (nota1*1 + nota2*2) / 3

    for (int i = 0; i < nAlunos; i++) {
        //printf("%s %.1f\n", alunos[i].nome, (alunos[i].materia.nota1 * 1 + alunos[i].materia.nota2 * 2) / 3);
    }
    return 0;
}