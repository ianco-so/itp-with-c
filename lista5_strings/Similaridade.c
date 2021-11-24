//Compare the similarity of two strings.
#include <stdio.h>
#include <string.h>

#define MAX_STR_LEN 10

void fill_strings(int nstr, char str[nstr][MAX_STR_LEN]){
    for (int i = 0; i < nstr; i++) {
        fgets(str[i], MAX_STR_LEN, stdin);
        str[i][strlen(str[i]) - 1] = '\0';
    }
}
void handle_similarity (int nstr, char str[nstr][MAX_STR_LEN], int similarity [nstr][nstr][2]){
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
int main (void) {
    int nstr = 0;
    scanf("%d\n", &nstr);

    int similarity[nstr][nstr][2];
    char str[nstr][MAX_STR_LEN];
    fill_strings(nstr, str);

    handle_similarity(nstr, str, similarity);

    //Prints the similarity matrix
    char strspace[MAX_STR_LEN];
    for (int i = 0; i < MAX_STR_LEN-1; i++) strspace[i] = ' ';
    strspace[MAX_STR_LEN-1] = '\0';
    for (int i = 0; i < nstr+1; i++) {
        for (int j = 0; j < nstr+1; j++) {
            if (i == 0 && j == 0) printf("%s", strspace);
            else if (i == 0) printf("%s%s", str[j-1],strspace);
            else if (j == 0) printf("%s%s", str[i-1],strspace);
            else printf("%d/%d%s", similarity[i-1][j-1][0], similarity[i-1][j-1][1], strspace);
        }
        printf("\n");
    }
    /*
    for (int i = 0; i < nstr; i++) {
        for (int j = 0; j < nstr; j++) {
            printf("%d/%d ", similarity[i][j][0], similarity[i][j][1]);
        }
        printf("\n");
    }
    */

    return 0;
}