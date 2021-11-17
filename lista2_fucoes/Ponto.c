//Let's check if the point (the first input) is near of one of the points (others inputs)
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

bool isNear(int A[2], int B[2]) {
    int const L = 3; //Only isNear need to know the limit of the distance
    if (sqrt(pow(A[0]- B[0], 2) + pow(A[1] - B[1], 2)) <= L)    return true; //If the distance is less than L, the point is near of the first point
    else  return false;
}

bool treatPoints(int A[2], int nPoints) {
    bool test = false;
    for (int i = 0; i < nPoints; i++) {
        int B[2];
        scanf("%d %d", &B[0], &B[1]);   //Read the points
        if (isNear(A, B)) test = true;  //if any point is near to de first point, turn the near variable to true
    }
    return test;
}

int main (void) {
    int mouse[2], nPoint = 0;
    
    scanf("%i %i", &mouse[0], &mouse[1]); //Read and save the input where the mouse clicked
    scanf("%i", &nPoint); //Read the number of points that will be treated
    treatPoints(mouse, nPoint)? printf("S"): printf("N");  //If near is false is because none of the points is near of the first point
    
    return 0;
}