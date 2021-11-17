#include <stdio.h>
#include <math.h>
#include <stdbool.h>
/*Note:
In this code i will always give names to vectos with two capital latters, 
and the dots will be named with one capital letter
*/
double dotProduct (int VA[2], int VB[2]) { //VA and VB are vectors
    return VA[0] * VB[0] + VA[1] * VB[1];
}
double vectorModule(int VA[2]) { // VA is vector A
    return (double) sqrt(pow(VA[0], 2) + pow(VA[1], 2));
}
double crossProduct(int VA[2], int VB[2]) { // calculate the cross product of two vectors
    return (double) (VA[0]*VB[1] - VA[1]*VB[0]);
}

double nearTheLine(int A[2], int B[2], int C[2]) {
    int AB[2] = {B[0] - A[0], B[1] - A[1]};
    int AC[2] = {C[0] - A[0], C[1] - A[1]};
    return fabs(crossProduct(AB, AC)/vectorModule(AB));
}

double beyondTheEdge(int A[2], int B[2], int C[2]) {    //Chack if the C dot is beyond the vec AB and return the distance, if not beyond return -1
    int AB[2] = {B[0] - A[0], B[1] - A[1]};
    int AC[2] = {C[0] - A[0], C[1] - A[1]};
    int BC[2] = {C[0] - B[0], C[1] - B[1]};
    if (dotProduct(AB, AC) > 0) return vectorModule(AC);
    else if (dotProduct(AC, BC) > 0)    return vectorModule(BC);
    else    return -1;
}

bool isNear (int A[2], int B[2], int C[2]) {
    const int L = 3;
    if (!(B[0] == -1)){
        if (beyondTheEdge(A, B, C) => 0 && beyondTheEdge(A, B, C) < L)   return true;
        else if (nearTheLine(A, B, C) < L)    return true;
        else  return false;
    } else  return false;
}

bool treatPoints (int C[2], int nPoint){
    int A[2] = {-1, -1}, B[2] = {-1, -1};
    bool test = false;

    for (int i = 0; i < nPoint; i++) {
        scanf("%i %i",&A[0],&A[1]);
        if(isNear(A,B,C))   test = true;
        else { //Saving the point that has been passed to verify it with the antecessor
            B[0] = A[0];
            B[1] = A[1];
        }
    }
    return test;
}

int main (void) {
    int mouse [2], nPoint = 0;

    scanf("%d %d", &mouse[0], &mouse[1]);
    scanf("%d", &nPoint);
    treatPoints(mouse, nPoint)? printf("S"): printf("N");

    return 0;
}