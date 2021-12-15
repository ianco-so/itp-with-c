#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 300
#define PART_SIZE 9

typedef struct number_array {
    unsigned int *array;
    unsigned int *missing_zeros;
    unsigned int size;    
} narray;

typedef struct big_float {
    int signal;
    int exp;
    narray integer;
    narray fractional;
} BigFloat;

void readline(char line[MAX_LINE]) {
    fgets(line, MAX_LINE, stdin);
    line[strlen(line) - 1] = '\0';
}

narray dealing_with_numerical_parts (char *part) {
    narray n;
    char *foo = NULL;
    int jump = 0;

    foo = calloc(PART_SIZE, sizeof(char));
    n.size = strlen(part)%PART_SIZE == 0 ? strlen(part)/PART_SIZE : strlen(part)/PART_SIZE + 1; //get the size of the integer part
    n.array = (unsigned int *)calloc(n.size, sizeof(unsigned int)); //allocate memory for the integer part
    if (n.size == strlen(part)/PART_SIZE + 1) {
        jump = strlen(part)%PART_SIZE;
        strncpy(foo, part, jump);
        n.array[n.size-1] = atoi(foo);
        for (int i = n.size-2; i >= 0; i--) {
            strncpy(foo, part + jump, PART_SIZE);
            jump += PART_SIZE;
            n.array[i] = atoi(foo);
        }
    } else {
        for (int i = n.size-1; i >= 0; i--) {
            strncpy(foo, part + i*PART_SIZE, PART_SIZE);
            n.array[i] = atoi(foo);
        }
    }
    free(foo);
    return n;
}

BigFloat strToBigFloat(char str[MAX_LINE]) {
    BigFloat bf;
    char *intPart = NULL , *fracPart = NULL;
    char *foo = NULL;
    int i = 0;
    //find the signal
    if (str[0] == '-') {
        bf.signal = -1;
        str[0] = '0';
    } else {
        bf.signal = 1;
    }

    //handle the integer part
    intPart = strtok(str, ".");
    bf.integer = dealing_with_numerical_parts(intPart);

    // handle with the exponent
    i = 0;
    fracPart = strtok(NULL, "."); //get the fractional part
    while (fracPart[0] == '0') {
        fracPart = memmove(fracPart, fracPart + 1, strlen(fracPart));
        i++;
    }
    bf.exp = i;
    
    //handle with the fractional part
    bf.fractional = dealing_with_numerical_parts(fracPart);
    
    return bf;
}
void printBigFloat (BigFloat bf) {
    if (bf.signal == -1) {
        printf("-");
    }
    for (int i = bf.integer.size-1; i >= 0; i--) {
        printf("%d", bf.integer.array[i]);
    }
    printf(".");
    for (int i = bf.fractional.size-1; i >= 0; i--) {
        printf("%d", bf.fractional.array[i]);
    }
    printf("\n");
}

int main() {
    char line[MAX_LINE];
    readline(line);
    BigFloat bf = strToBigFloat(line);
    printBigFloat(bf);
    printf("%i %u %u %u\n",
        bf.signal,
        bf.exp,
        bf.integer.array[bf.integer.size - 1],
        bf.fractional.array[bf.fractional.size - 1]
    );
    return 0;
}