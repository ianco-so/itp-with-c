//chack if a sequence of numbers has subsequences of consecutive numbers
#include <stdio.h>
#include <string.h>

#define MAX_SIZE 1000

int check_sequence(char sequence[]) {
    int count = 0;
    int count2 = 0;
    for (int i = 0; i < strlen(sequence); i++) {
        if (sequence[i]-'0'+1 == sequence[i+1]-'0') {
            count++;
            if (count == 4) {
                count2++;
                count = 0;
            }
        } else {
            count = 0;
        }
    }
    return count2;
}

int main (void) {
    char sequence[MAX_SIZE];
    scanf("%s", sequence);
    check_sequence(sequence) == 0 ? printf("nenhuma sequencia encontrada") : printf("%d", check_sequence(sequence));
    return 0;
}