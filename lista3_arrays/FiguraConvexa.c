//Check if the points clicked are inside the convex figure
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void fflush_stdin() {  //To see more chack this answer https://stackoverflow.com/a/30222001/16295366 
    while (getchar() != '\n' && getchar() != EOF); 
}

double crossProduct(int V1[2], int V2[2]) { // calculate the cross product of two vectors
    return (double) (V1[0]*V2[1] - V1[1]*V2[0]);
}
bool onRight (int A[2], int B[2], int C[3]) {
    int V1[2] = {B[0] - A[0], B[1] - A[1]};
    int V2[2] = {C[1] - A[0], C[2] - A[1]};
    if (crossProduct(V1, V2) <= 0) {
        return true;
    
    }else {
        return false;
    }
}

void testPoints(int n, int m, int fPoints[n][2], int mPoints[m][3]) {
    for (int i = 0; i < m; i++) {
        bool test = true;
        for (int j = 1; j < n; j++) {
            if (j == n) {
                if (!onRight(fPoints[j-1], fPoints[0], mPoints[i])) {
                    test = false;
                }
            }
            if (!onRight(fPoints[j-1], fPoints[j], mPoints[i])) {
                test = false;
            }
        }
        if (test) printf("%c\n", mPoints[i][0]);
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