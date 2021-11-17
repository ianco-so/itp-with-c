//Check if the first inputted point  is near of the lines formed by the other points that will been inputted
#include <stdio.h>
#include <math.h>
#include <stdbool.h>


double vectorModule(int A[2], int B[2]) { // calculate the vector module (or the distance amid two points)
    return (double) sqrt(pow(A[0]- B[0], 2) + pow(A[1] - B[1], 2));
}
double crossProduct(int A[2], int B[2], int C[2]) { // calculate the cross product of two vectors
    return (double) ((A[0] - B[0]) * (A[1] - C[1]) - (A[1] - B[1]) * (A[0] - C[0]));
    //( (A[0] - B[0]) * (C[1] - B[1]) - (A[1] - B[1]) * (C[0] - B[0]) );
}

bool isNearOfLine(int A[2], int B[2], int C[2]) { // check if the point C is near of the line formed by A and B
    if (!(B[0] == -1)){  //as B coordinates may not been passed yet, i have to verify this before testing anything
        const int L = 3; //Only isNearOfLine function need to know the limit distance of the line
        double distance = fabs(crossProduct(A, B, C)/vectorModule(A, B));
        if (distance < L)   return true;
        else    return false;
    } else return false;
}

bool treatPoints (int C[2], int nPoint){
    int A[2] = {-1, -1}, B[2] = {-1, -1};
    bool test = false;
    for (int i = 0; i < nPoint; i++) {
        scanf("%i %i",&A[0],&A[1]);
        if(isNearOfLine(A,B,C)) test = true;
        else { //Saving the point that has been passed to verify it with the antecessor
            B[0] = A[0];
            B[1] = A[1];
        }
    }
    return test;
}

int main (void) {
    int mouse[2], nPoint = 0;

    scanf("%i %i",&mouse[0],&mouse[1]);
    scanf("%i", &nPoint);
    treatPoints(mouse, nPoint)? printf("S"): printf("N");

    return 0;
}