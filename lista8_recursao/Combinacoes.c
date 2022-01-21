//Print all combinations of a given number of factors

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

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

//Generate all combinations of factors with the recursive method
void generate_combinations(int n, int *values, int * current, int i){
    if (i < n) {
        if (current[n-1] < values[n-1]) {
            print_values(n, current);
            current[n-1]++;
            generate_combinations(n, values, current, i);
        } else { //if (current[n-1] == values[n-1]) 

            //reset all values to 0 after the desired value
            memset(current+n-1-i, 0, n*sizeof(int));
            /*
            for(int j=n-1-i;j<=n-1;j++){
                current[j] = 0;
            }
            */
            i++;
            current[n-1-i]++;
            generate_combinations(n, values, current, i);
        }
    } else if (i == n) {
        
    }
}

int main (void) {
    int n = 0; //quantity of factors
    scanf("%d", &n);
    int * values = calloc(n, sizeof(int)); //quantity of values in each factor
    int * current = calloc(n, sizeof(int)); //current combination of factors
    read_values(n, values);
    generate_combinations(n, values, current, 0);
    return 0;
}
