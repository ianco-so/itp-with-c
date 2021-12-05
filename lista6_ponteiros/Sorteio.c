#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define STR_LENGTH 10

char ** alloc_lines(int l, char **lines) {
    if (lines == NULL) {
        lines = malloc(sizeof(char *));
        if (lines == NULL) {
            printf("Error: malloc failed\n");
            exit(1);
        }
    } else {
        lines = realloc(lines, (l+1) * sizeof(char *));
        if (lines == NULL) {
            printf("Error: realloc failed\n");
            exit(1);
        }
    }
    return lines;
}

void store_line (char str[], int l, char** lines) {
	if(lines[l] == NULL){
		lines[l] = malloc(sizeof(char)*(strlen(str)+1));
        if (lines[l] == NULL) {
            printf("Error: malloc failed\n");
            exit(1);
        }
		strcpy(lines[l],"");
	}
	else {
		lines[l] = realloc(lines[l], sizeof(char)*(strlen(lines[l])+strlen(str)+1));
        if (lines[l] == NULL) {
            printf("Error: realloc failed\n");
            exit(1);
        }
    }
	strcat(lines[l],str);
}

char ** create_participant_list (char** lines, int *n_lines) {
    char str[STR_LENGTH];
    int l = 0;
    bool allocnext = true, end = false;

    while (!end) { //when the user write "end" stop reading
        //printf("Digite o nome do participante: ");
        fgets(str, STR_LENGTH, stdin);
        if (strcmp(str, "acabou\n") != 0) {
            if (allocnext == true) {
                lines = alloc_lines(l, lines);
                lines[l] = NULL;
                allocnext = false;
            }
            store_line(str,l, lines);
            if (str[strlen(str) - 1] == '\n') {
                //str[strlen(str) - 1] = '\0';
                allocnext = true;
                l++;
            }
        } else  end = true;
    }
    /*
    for (int i = 0; i < *n_lines; i++)
        for (int j = 0; j < strlen(lines[i]); j++)
            if (lines[i][j] == '\n')    lines[i][j] = '\0';
    */
    *n_lines = l;
    return lines;
}
int main (void) {
    char** participantes = NULL;
    int n_participant = 0, count = 0;
    int seed = 0;

    participantes = create_participant_list(participantes, &n_participant); //read, dynamically, mutiples lines of text
    scanf("%d", &seed); //After reading, the user must enter the seed for the random for the prize draw
    srand(seed);
    //the program must print the drawns in order they were drawn
    while (count < n_participant) {
        int random = rand() % n_participant;
        if (participantes[random] != NULL) {
            printf("%s", participantes[random]);
            participantes[random] = NULL;
            count++;
        }
    }
    for(int i=0; i<n_participant; i++) free(participantes[i]); //free memory
    free(participantes);

    return 0;
}