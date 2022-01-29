//Word Hunter
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

//if the word is not in the board, we will return a null pointer
char * hunt_words(char word[11], char board[10][10], int *steps){
    for (int i = 0; i <10; i++) {
        for (int j = 0; j <10; j++) {
            if (toupper(board[i][j]) == toupper(word[0])) {
                bool foundLR = true;
                bool foundLL = true;
                bool foundCD = true;
                bool foundCU = true;
                bool foundDDR = true;
                bool foundDDL = true;
                bool foundDUR = true;
                bool foundDUL = true;
                for (int k = 0; k < strlen(word); k++) {
                    if (toupper(board[i][j+k]) != toupper(word[k])) { //chack the line to the right
                        foundLR = false;
                    }
                    if (toupper(board[i][j-k]) != toupper(word[k])) { //chack the line to the left
                        foundLL = false;
                    }
                    if (toupper(board[i+k][j]) != toupper(word[k])) { //chack the column down
                        foundCD = false;
                    }
                    if (toupper(board[i-k][j]) != toupper(word[k])) { //chack the column up
                        foundCU = false;
                    }
                    if (toupper(board[i+k][j+k]) != toupper(word[k])) { //chack the diagonal down-right
                        foundDDR = false;
                    }
                    if (toupper(board[i+k][j-k]) != toupper(word[k])) { //chack the diagonal down-left
                        foundDDL = false;
                    }
                    if (toupper(board[i-k][j+k]) != toupper(word[k])) { //chack the diagonal up-right
                        foundDUR = false;
                    }
                    if (toupper(board[i-k][j-k]) != toupper(word[k])) { //chack the diagonal up-left
                        foundDUL = false;
                    }
                    if  (!foundLR && !foundLL && !foundCD && !foundCU && !foundDDR && !foundDDL && !foundDUR && !foundDUL) {
                        break;
                    }
                }
                if(foundLR) {
                    *steps = 1;
                    return &board[i][j];
                }
                if (foundLL) {
                    *steps = -1;
                    return &board[i][j];
                }
                if (foundCD) {
                    *steps = 10;
                    return &board[i][j];
                }
                if (foundCU) {
                    *steps = -10;
                    return &board[i][j];
                }
                if (foundDDR) {
                    *steps = 11;
                    return &board[i][j];
                }
                if (foundDDL) {
                    *steps = 9;
                    return &board[i][j];
                }
                if (foundDUR) {
                    *steps = -9;
                    return &board[i][j];
                }
                if (foundDUL) {
                    *steps = -11;
                   return &board[i][j];    
                }
            }
        }
    }
    return NULL;
}

//if, the return, is a not null pointer, we will print the words (how was find in the board) and the number of steps
void imprimePalavra (char *c, int salto, int tam) {
    if (c==NULL) {
        printf("Palavra nao encontrada\n");
        return;
    }
    for (int i=0; i<tam; i++) {
        printf("%c", *c);
        c+=salto;
    }
    printf(", salto:%d\n", salto);
}

int main (void) {
    //initially, we will to read the number of the words to be hunted
    char board[10][10], *w;
    int n, steps = 0;
    scanf("%d", &n);
    getchar();
    //then we will read the words
    char words[n][11];
    for (int i = 0; i < n; i++) {
        fgets(words[i], 11, stdin);
        if (words[i][strlen(words[i])-1] == '\n')   words[i][strlen(words[i])-1] = '\0';
    }
    //further we going to read a matrix 10x10 of letters which will be the board (the words will be in the board)
    for (int i = 0; i < 10; i++) {
        scanf("%s", board[i]);
    }
    //for each word we will verify if it is in the board, if it is,
    // we will return the position of the first letter of the word and the steps for the letters following it
    for (int i = 0; i < n; i++) {
        w = hunt_words(words[i], board, &steps);
        imprimePalavra(w, steps, strlen(words[i]));
    }
    return 0;
}