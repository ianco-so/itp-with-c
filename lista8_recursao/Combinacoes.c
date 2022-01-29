//Print all combinations of a given number of factors

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define true 1
#define false 0


//Read the quantity of values in each factor
void read_values(int n, int * values){
    for(int i=0;i<n;i++){
        scanf("%d", &(values[i]));
    }
}

//Print the current combination of factors
void print_values(int n, int * current){
    printf("<%d", current[0]);
        for(int i=1;i<n;i++){
            printf(", %d", current[i]);    
        }    
    printf(">\n");    
}

//Test if the current combination is equal to the target
int in_target(int n, int * current, int * target){
    for(int i=0;i<n;i++){
        if((current[i]+1)!=target[i]){
            return false;
        }
    }
    return true;
}

//Generate all combinations of factors with the recursive method
void generate_combinations(int n, int *values, int * current, int i){
    if (in_target(n, current, values)){
        print_values(n, current);
        return;
    }
    if (i < n && current[n-1-i] < values[n-1-i]){
        print_values(n, current);
        current[n-1-i]++;
        generate_combinations(n, values, current, i);
        current[n-1-i] = 0;
    }
    if 
}
/*
//Generate all combinations of factors with the recursive method
void generate_combinations(int n, int *values, int * current, int i){
    if (current[n-1-i] < values[n-1-i]){
        print_values(n, current);
        current[n-1-i]++;
        generate_combinations(n, values, current, i);
    } else if (i < n-1) {
        current[n-1-i] = 0;
        current[n-2-i]++;
        generate_combinations(n, values, current, i+1);
    }
        
}
*/
int main (void) {
    int n = 0; //quantity of factors
    scanf("%d", &n);
    int * values = calloc(n, sizeof(int)); //quantity of values in each factor
    int * current = calloc(n, sizeof(int)); //current combination of factors
    read_values(n, values);
    //print_values(n, current);
    //print_values(n, values);
    generate_combinations(n, values, current, 0);
    return 0;
}
