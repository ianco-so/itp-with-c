//Ler os dados de, até 10 alunos e depois calcula e mostra a média de cada um.
#include <stdio.h>
#include <ctype.h>

typedef struct DISCIPLINA {
    int codigo;
    double nota1;
    double nota2;
} Materia;

typedef struct ESTUDANTE{
    char nome[50];
    int matricula;
    Materia materia;
}Aluno;

int main (void) {
    int nAlunos = 0;
    scanf("%d", &nAlunos);
    Aluno alunos[nAlunos];
    getchar();

    for (int i = 0; i < nAlunos; i++) {
        scanf("%d, %[^,] , %d, %f , %f", &alunos[i].matricula, alunos[i].nome, &alunos[i].materia.codigo, &alunos[i].materia.nota1, &alunos[i].materia.nota2);
    }
    printf("\n");
    printf("Nota 1: %f\n", alunos[0].materia.nota1);
    printf("Nota 2: %f\n", alunos[0].materia.nota2);
    //calculando e exibindo a media ponderada de cada aluno (nota1*1 + nota2*2) / 3

    for (int i = 0; i < nAlunos; i++) {
        //To upper case the frist letter of the name
        alunos[i].nome[0] = toupper(alunos[i].nome[0]);
        printf("%s,média final = %.f\n", alunos[i].nome, (alunos[i].materia.nota1 * 1 + alunos[i].materia.nota2 * 2)/3);
    }
    return 0;
}