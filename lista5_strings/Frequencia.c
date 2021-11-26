#include <stdio.h>
#include <string.h>

#define MAX_SIZE 256

//counts how many times a string is substring of another string
int count_substring(char *str, char *sub){
    int cnt = 0;
    char *p;
    while (p = strstr(str, sub)){
        str = p + 1;
        ++cnt;
    }
    return cnt;
}

//count the number of words in the each entry
int count_words(char *str){
    int cnt = 0;
    for (int i = 0; i <= strlen(str); i++) {
        if (str[i] == ' ' || str[i] == '\0')  cnt++;
    }
    return cnt;
}

int main (void) {
    char ref_word[MAX_SIZE];
    char phrase[MAX_SIZE] = {'\0'};
    int cnt_words = 0, cnt_occurrences = 0, cnt_words_total = 0, cnt_occurrences_total = 0;
    //Read the reference word
    scanf("%s", ref_word);
    getchar();
    while (strcmp(phrase, "-1") != 0){
        //Read, with a while loop, the nexts entries
        fgets(phrase, MAX_SIZE, stdin);
        phrase[strlen(phrase) - 1] = '\0';
        if (strcmp(phrase, "-1") == 0) break;
        cnt_words = count_words(phrase);
        cnt_occurrences = count_substring(phrase, ref_word);
        printf("%.4f\n", cnt_occurrences / (float)cnt_words);
        //count the total number of words in all entries
        cnt_words_total += cnt_words;
        //count the total number of times the given string appears in all phrases
        cnt_occurrences_total += cnt_occurrences;
    }
    printf("%.4f\n", cnt_occurrences_total / (float)cnt_words_total);
    return 0;
}