#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 200

typedef struct team {
    char *name;
    //int MP // Matches Played
    int W; // Wins
    int D; // Draws
    int L; // Losses
    int GF; // Goals For
    int GA; // Goals Against
} Team;

Team read_team() {
    Team t;
    char *part, line[MAX_NAME_LEN];
    fgets(line, 200, stdin);
    part = strtok(line, ";");
    t.name = malloc(strlen(part) + 1);
    strcpy(t.name, part);
    part = strtok(NULL, ";");
    sscanf(part, "%d %d %d %d %d", &t.W, &t.D, &t.L, &t.GF, &t.GA);
    return t;
    
}
//Bubble sort
void sort_teams (int n, Team t[n]) {
    Team temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i+1; j < n; j++) {
            //points = t.W * 3 + t.D;
            if (t[i].W * 3 + t[i].D < t[j].W * 3 + t[j].D) {
                temp = t[i];
                t[i] = t[j];
                t[j] = temp;
            } else if (t[i].W * 3 + t[i].D == t[j].W * 3 + t[j].D && t[i].W < t[j].W) {
                temp = t[i];
                t[i] = t[j];
                t[j] = temp;
            } else if (t[i].W == t[j].W && t[i].GF - t[i].GA < t[j].GF - t[j].GA) {
                temp = t[i];
                t[i] = t[j];
                t[j] = temp;
            }
        }
    }
}

void print_standings(Team *t, int n) {
    printf("Tabela do campeonato:\n");
    printf("Nome| Pontos| Jogos| Vitorias| Empates| Derrotas| Gols Pro| Gols Contra| Saldo de Gols\n");
    for (int i = 0; i < n; i++) {
        printf("%s| %d| %d| %d| %d| %d| %d| %d| %d\n", t[i].name, t[i].W*3 + t[i].D, t[i].W + t[i].D + t[i].L, t[i].W, t[i].D, t[i].L, t[i].GF, t[i].GA, t[i].GF - t[i].GA);
    }
    printf("\n");
    printf("Times na zona da libertadores:\n");
    for (int i = 0; i < 6; i++) {
        printf("%s\n", t[i].name);
    }
    printf("\n");
    printf("Times rebaixados:\n");
    for (int i = n - 1; i > n - 5; i--) {
        printf("%s\n", t[i].name);
    }
}

int main (void) {
    int n_teams = 0;
    scanf("%d", &n_teams);
    getchar();
    Team *teams = malloc(n_teams * sizeof(Team));
    for (int i = 0; i < n_teams; i++) {
        teams[i] = read_team();
    }
    sort_teams(n_teams, teams);
    print_standings(teams, n_teams);


    for (int i = 0; i < n_teams; i++) {
        free(teams[i].name);
    }
    free(teams);
    return 0;
}