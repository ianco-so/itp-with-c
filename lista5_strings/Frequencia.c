//count the number of times the given string appears in the phrase and divide by the number of words in the phrase
//calculate the frequency and print it
#include <stdio.h>
#include <string.h>

#define MAX_SIZE 255

int main (void) {
    char reference_word[MAX_SIZE];
    char phrase[MAX_SIZE] = {'\0'};
    int count_words = 0, count_occurrences = 0, count_words_total = 0, count_occurrences_total = 0;
    //Read the reference word
    scanf("%s", reference_word);
    getchar();
    while (strcmp(phrase, "-1") != 0){
        //Read, with a while loop, the nexts entries
        fgets(phrase, MAX_SIZE, stdin);
        phrase[strlen(phrase) - 1] = '\0';
        if (strcmp(phrase, "-1") == 0) break;
        //count the number of words in the each entry
        for (int i = 0; i <= strlen(phrase); i++) {
            if (phrase[i] == ' ' || phrase[i] == '\0') {
                count_words++;
            }
        }

        for (int i = strlen(phrase) - strlen(strstr(phrase, reference_word)); i < strlen(phrase); i++) {
            //count the number of occurrences of the reference word in the entry
            if (strstr(phrase, reference_word) != NULL) {
                count_occurrences++;
            }
        }
        printf("%d\n", count_occurrences);
        //count the total number of words in all entries
        count_words_total = count_words_total + count_words;
        count_words = 0;
        //count the total number of times the given string appears in all phrases and the number of words in all phrases
        count_occurrences_total = count_occurrences_total + count_occurrences;
        count_occurrences = 0;
    }
    printf("%d, %d, %d", count_words, count_words_total, count_occurrences_total);
    return 0;
}