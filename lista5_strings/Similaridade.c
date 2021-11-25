//Compare the similarity of two strings.
#include <stdio.h>
#include <string.h>

#define MAX_STR_LEN 10

void fill_strings(int nstr, char str[nstr][MAX_STR_LEN]){
    for (int i = 0; i < nstr; i++) {
        fgets(str[i], MAX_STR_LEN+1, stdin);
        str[i][strlen(str[i]) - 1] = '\0';
    }
}
void handle_similarity (int nstr, char str[nstr][MAX_STR_LEN], int similarity[nstr][nstr][2]){
    //Initialize the similarity matrix with 0
    for (int i = 0; i < nstr; i++)  for (int j = 0; j < nstr; j++)  similarity[i][j][0] = similarity[i][j][1] = 0;
    //compares strings bitwise
    for (int i = 0; i < nstr; i++) {
        for (int j = 0; j < nstr; j++) {
            if (strlen(str[i]) <= strlen(str[j])) {
                similarity[i][j][1] = strlen(str[j]);
                for (int k = 0; k < strlen(str[i]); k++) {
                    if (str[i][k] == str[j][k]) similarity[i][j][0]++;
                }
            } else {
                similarity[i][j][1] = strlen(str[i]);
                for (int k = 0; k < strlen(str[j]); k++) {
                    if (str[i][k] == str[j][k]) similarity[i][j][0]++;
                }
            }
        }
    }
}
void print_results (int nstr, char str[nstr][MAX_STR_LEN], int similarity[nstr][nstr][2]){
    for (int i = 0; i < nstr+1; i++) {
        for (int j = 0; j < nstr+1; j++) {
            if (i == 0 && j == 0) for (int k = 0; k < MAX_STR_LEN; k++) printf(" ");
            else if (i == 0) {
                for (int k = strlen(str[j-1]); k < MAX_STR_LEN; k++)    printf(" ");
                for (int k = 0; str[j-1][k] != '\0'; k++)   printf("%c", str[j-1][k]);
            }
            else if (j == 0) {
                for (int k = 0; str[i-1][k] != '\0'; k++)   printf("%c", str[i-1][k]);
                for (int k = strlen(str[i-1]); k < MAX_STR_LEN; k++)    printf(" ");
            }
            else {
                for (int k = 3; k < MAX_STR_LEN; k++)   printf(" ");
                printf("%d/%d", similarity[i-1][j-1][0], similarity[i-1][j-1][1]);
            }
        }
        printf("\n");
    }
}
int main (void) {
    int nstr = 0;
    scanf("%d\n", &nstr);
    int similarity[nstr][nstr][2];
    char str[nstr][MAX_STR_LEN];
    fill_strings(nstr, str);
    handle_similarity(nstr, str, similarity);
    print_results(nstr, str, similarity);
    return 0;
}