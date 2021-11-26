//remove prefix and suffix

#include <stdio.h>
#include <string.h>

#define PRE_SUF_SIZE 10
#define SIZE 100

//to see more check https://stackoverflow.com/questions/47116974/remove-a-substring-from-a-string-in-c?answertab=oldest#tab-top
char *strremove(char *str, int nprefix, int nsuffix ,const char pre[nprefix][PRE_SUF_SIZE], const char suf[nsuffix][PRE_SUF_SIZE]){
    for (int i = 0; i < nprefix; i++) {
        if (strlen(pre[i]) > 0) {
            char *p = str;
            while (p = strstr(p, pre[i])) {
                memmove(p, p + strlen(pre[i]), strlen(p + strlen(pre[i])) + 1);
            }
        }
    }
    for (int i = 0; i < nsuffix; i++) {
        if (strlen(suf[i]) > 0) {
            char *p = str;
            while (p = strstr(p, suf[i])) {
                memmove(p, p + strlen(suf[i]), strlen(p + strlen(suf[i])) + 1);
            }   
        }
    }
    return str;
}

int main (void) {
    int nprefix = 0, nsuffix = 0;
    //Read the prefixes
    scanf("%d", &nprefix);
    char prefix[nprefix][PRE_SUF_SIZE];
    for (int i = 0; i < nprefix; i++) {
        scanf("%s", prefix[i]);
    }
    //Read the suffixes
    scanf("%d", &nsuffix);
    char suffix[nsuffix][PRE_SUF_SIZE];
    for (int i = 0; i < nsuffix; i++) {
        scanf("%s", suffix[i]);
    }
    //Read the words
    char word[SIZE] = {'\0'};
    do {
        scanf("%s", word);
        if (strcmp(word, "-1") == 0) break;
        //char *removed_word = strremove(word, prefix, prefix);
        printf("%s\n", strremove(word, nprefix, nsuffix, prefix, suffix));
    } while (strcmp(word, "-1") != 0);
    return 0;
}