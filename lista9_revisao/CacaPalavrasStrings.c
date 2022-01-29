#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 50
#define MAX_WORD_LENGTH 19

int main (void) {
    char word[MAX_WORD_LENGTH];
    char line[MAX_LINE_LENGTH];
    char  *w;
    char **found_words = calloc(1, sizeof(char*));
    int found_words_index = 1;

    fgets(word, MAX_WORD_LENGTH, stdin);
    if (word[strlen(word)-1] == '\n') word[strlen(word)-1] = '\0';

    while(scanf("%s", line) != EOF) {
        w = strtok(line, " ");
        while(w != NULL) {
            if (strstr(w, word) != NULL) {
                found_words = realloc(found_words, sizeof(char*) * (found_words_index+1));
                found_words[found_words_index] = calloc(strlen(w)+1, sizeof(char));
                strcpy(found_words[found_words_index], w);
                found_words_index++;
            }
            w = strtok(NULL, " ");
        }
    }
    for (int i = 0; i < found_words_index; i++) {
        printf("%s\n", found_words[i]);
    }
    free(found_words);
    return 0;
}

/*
*/
