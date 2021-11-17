//This algorithm is for checking if the clicked point is part or is near of the lines of which points will be passed
#include<stdio.h>
#include<math.h>
#include<stdbool.h>

bool inLine(int A[2], int B[2], int mouse[2]){ //mouse is in the same line as A and B?
    if (!(B[0] == -1)){  //as B coordinates may not been passed yet, i have to verify this before testing anything
        double m = (double) (B[1] - A[1]) / (double) (B[0] - A[0]); //calculating m
        if(mouse[1]  == (int) (m*(mouse[0] - A[0]) + A[1] + 0.5))   return true; //Chack if mouse satisfy the AB straight equation
        else    return false;
    } else  return false;
}

/*this function read the points and pass them to the inLine function, 
if inLine return true one single time, so this function can return true too*/
bool treatPoints (int mouse[2], int nPoint){
    int A[2] = {-1, -1}, B[2] = {-1, -1};
    bool test = false;
    for (int i = 0; i < nPoint; i++) {
        scanf("%i %i",&A[0],&A[1]);
        if(inLine(A,B,mouse))   test = true;
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