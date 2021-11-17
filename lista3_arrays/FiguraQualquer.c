#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void fflush_stdin() {  //To see more chack this answer https://stackoverflow.com/a/30222001/16295366 
    while (getchar() != '\n' && getchar() != EOF); 
}
bool inRange (int A[2], int B[2], int C[3]) {
    int range[2];
    if (A[1] < B[1]) {
        range[0] = A[1];
        range[1] = B[1];
    } else {
        range[0] = B[1];
        range[1] = A[1];
    }
    if (C[2] >= range[0] && C[2] <= range[1])   return true;
    else return false;
}
double crossProduct(int V1[2], int V2[2]) { // calculate the cross product of two vectors
    return (double) (V1[0]*V2[1] - V1[1]*V2[0]);
}
bool crossTheLine (int A[2], int B[2], int C[3], int max) { // check if the vector AB cross the vector C {max, C[2]}
    int D[2] = {max, C[2]};
    int AB[2] = {B[0] - A[0], B[1] - A[1]};
    int AC[2] = {C[1] -A[0], C[2] - A[1]};
    int AD[2] = {D[0] - A[0], D[1] - A[1]};
    if (inRange (A, B, C)) {
        if( (crossProduct(AB, AC) > 0 && crossProduct(AB, AD) < 0) || (crossProduct(AB, AC) < 0 && crossProduct(AB, AD) > 0) ) return true;
        else  return false;
    } else return false;
}

void testPoints(int n, int m, int fPoints[n][2], int mPoints[m][3]) {
    int max = 0;
    for (int i = 0; i < n; i++) if(fPoints[i][0] > max) max = fPoints[i][0];
    for (int i = 0; i < m; i++) {
        int crossLine = 0;
        for (int j = 1; j <= n; j++) {
            if(j == n)  if(crossTheLine(fPoints[j-1], fPoints[0], mPoints[i], max))    crossLine++;
            else if(crossTheLine(fPoints[j-1], fPoints[j], mPoints[i], max))   crossLine++;
        }
        if (crossLine%2 > 0) printf("%c\n", mPoints[i][0]);
    }
}

int main (void) {
    int n, m;
    scanf("%d %d", &n, &m);
    int fPoints[n][2], mPoints[m][3]; //figure points and mouse points
    for (int i = 0; i < n; i++) { //read the figure points
        scanf("%d %d", &fPoints[i][0], &fPoints[i][1]);
    }
    for (int i = 0; i < m; i++) {//read the mouse points (points clicked)
        char id;
        fflush_stdin(); //to clean the buffer of the scanf
        scanf("%c %d %d", &id, &mPoints[i][1], &mPoints[i][2]);
        mPoints[i][0] = id; //Read the id like a char and convert it to int (ascii)
    }
    testPoints(n, m, fPoints, mPoints);
    return 0;
}