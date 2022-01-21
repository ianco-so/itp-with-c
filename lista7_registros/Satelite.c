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
    //line[strlen(line)] = '\0';
    line[strlen(line) - 1] = '\0';
}

int count_digits(int n) {
    int count = 0;
    while (n > 0) {
        n /= 10;
        count++;
    }
    return count;
}

narray init_narray(int size) {
    narray a;
    a.size = size;
    a.array = (unsigned int *)calloc(a.size, sizeof(unsigned int));
    a.missing_zeros = (unsigned int *)calloc(a.size, sizeof(unsigned int));
    return a;
}

narray dealing_with_numerical_parts (char *part) {
    //printf("%s\n", part);
    narray n;
    char *foo = NULL;
    int jump = 0;

    foo = calloc(PART_SIZE, sizeof(char));
    n.size = strlen(part)%PART_SIZE == 0 ? strlen(part)/PART_SIZE : strlen(part)/PART_SIZE + 1; //get the size of the integer part
    n.array = (unsigned int *)calloc(n.size, sizeof(unsigned int)); //allocate memory for the integer part
    n.missing_zeros = (unsigned int *)calloc(n.size, sizeof(unsigned int));
    if (n.size != strlen(part)/PART_SIZE) {
        jump = strlen(part)%PART_SIZE;
        strncpy(foo, part, jump);
        n.array[n.size-1] = atoi(foo);
        for (int i = n.size-2; i >= 0; i--) {
            strncpy(foo, part + jump, PART_SIZE);
            jump += PART_SIZE;
            n.array[i] = atoi(foo);

            n.missing_zeros[i] = strlen(foo) - count_digits(n.array[i]);
        }
        n.missing_zeros[n.size - 1] = 0;
    } else {
        for (int i = n.size-1; i >= 0; i--) {
            strncpy(foo, part + jump, PART_SIZE);
            jump += PART_SIZE;
            n.array[i] = atoi(foo);
            n.missing_zeros[i] = strlen(foo) - count_digits(n.array[i]);
        }
        n.missing_zeros[n.size - 1] = 0;
    }

    free(foo);
    return n;
}

BigFloat strToBigFloat(char str[MAX_LINE]) {
    BigFloat bf;
    char *intPart = NULL , *fracPart = NULL, *foo = NULL;
    int i = 0;

    foo = calloc(MAX_LINE, sizeof(char));
    foo = strncpy(foo, str, strlen(str));
    //find the signal
    if (str[0] == '-') {
        bf.signal = -1;
        foo = memmove(foo, foo+1, strlen(foo));
    } else {
        bf.signal = 1;
    }

    if (foo[0] == '.') {
        bf.integer = init_narray(1);
        foo = memmove(foo, foo+1, strlen(foo));
        i = 0;
        while (foo[0] == '0') {
            foo = memmove(foo, foo + 1, strlen(foo));
            i++;
        }
        bf.exp = i;
        bf.fractional = dealing_with_numerical_parts(foo);
        while (bf.fractional.array[0] % 10 == 0) {
            bf.fractional.array[0] /= 10;
        }
        return bf;
    } else if (foo[strlen(foo)-1] == '.') {
        foo[strlen(foo)-1] = '\0';
        bf.exp = 0;
        bf.fractional = init_narray(1);
        bf.integer = dealing_with_numerical_parts(foo);
        return bf;
    } else {
        intPart = strtok(foo, ".");
        fracPart = strtok(NULL, ".");
        i = 0;
        while (fracPart[0] == '0') {
            fracPart = memmove(fracPart, fracPart + 1, strlen(fracPart));
            i++;
        }
        bf.exp = i;
        bf.integer = dealing_with_numerical_parts(intPart);
        bf.fractional = dealing_with_numerical_parts(fracPart);
        while (bf.fractional.array[0] % 10 == 0) {
            bf.fractional.array[0] /= 10;
        }
        return bf;
    }

    return bf;
}

void printBigFloat (BigFloat bf) {
    if (bf.signal == -1) {
        printf("-");
    }
    for (int i = bf.integer.size-1; i >= 0; i--) {
        for (int j = 0; j < bf.integer.missing_zeros[i]; j++) {
            printf("0");
        }
        printf("%d", bf.integer.array[i]);
    }
    printf(".");
    for (int i = 0; i < bf.exp; i++) {
        printf("0");
    }
    for(int i = bf.fractional.size-1; i >= 0; i--) {
        for (int j = 0; j < bf.fractional.missing_zeros[i]; j++) {
            printf("0");
        }
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