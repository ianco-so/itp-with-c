#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 50
#define MAX_WORD_LENGTH 19

//read the lines and find the words witch has like the key word as substring
char ** read_text(char ** found_words, char const * word, int * n_found_words) {
    char line[MAX_LINE_LENGTH];
    char *w;
    int count = 0;
    while(scanf("%s", line) != EOF) {
        w = strtok(line, " ");
        while(w != NULL) {
            if (strstr(w, word) != NULL) {
                found_words = realloc(found_words, sizeof(char*) * (count+1));
                found_words[count] = calloc(strlen(w)+1, sizeof(char));
                strcpy(found_words[count], w);
                count++;
            }
            w = strtok(NULL, " ");
        }
    }
    *n_found_words = count;
    return found_words;
}

//order the words in alphabetical order
void order_words(char ** words, int n_words) {
    char * aux;
    for (int i = 0; i < n_words; i++) {
        for (int j = i+1; j < n_words; j++) {
            if (strcmp(words[i], words[j]) > 0) {
                aux = words[i];
                words[i] = words[j];
                words[j] = aux;
            }
        }
    }
}
int main (void) {
    char word[MAX_WORD_LENGTH];
    char **found_words = calloc(1, sizeof(char*));
    int * n_found_words = calloc(1, sizeof(int));

    fgets(word, MAX_WORD_LENGTH, stdin);
    if (word[strlen(word)-1] == '\n') word[strlen(word)-1] = '\0';

    found_words = read_text(found_words, word, n_found_words);
    order_words(found_words, *n_found_words);

    for (int i = 0; i < *n_found_words; i++) {
        printf("%s\n", found_words[i]);
    }
    free(found_words);

    return 0;
}