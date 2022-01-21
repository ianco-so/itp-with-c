//Standard deviation with regration method
#include <stdio.h>
#include <math.h>

//Calculate the mean with the regression method
double mean(int n, int i, double sequence[n], int power) {
    if (i < n) {
        return pow(sequence[i], power)/n + mean(n, i + 1, sequence, power);
    } else {
        return 0;
    }
}

//Caclulate the variance
double variance(int n, int i, double sequence[n]) {
    if (i < n) {
        scanf("%lf", &sequence[i]);
        getchar();
        //printf("%lf\n", sequence[i]);
        return variance(n, i+1, sequence);
    } else {
        return mean(n, 0, sequence, 2) - pow(mean(n, 0, sequence, 1), 2);
    }
}

int main (void) {
    int n = 0;
    scanf("%d", &n);
    double sequence[n];
    printf("%.4lf\n", sqrt(fabs(variance(n, 0, sequence))));
    //printf("%.4lf\n",mean(n, 0, sequence, 1));
    return 0;
}