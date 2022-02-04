#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//recursive function that return true if the Pacman could eat one certain food and false otherwise
int canEat(int l, int c, char map[l][c], int checked[l][c], int pX, int pY, int fX, int fY) {
    int ate;
    //base case: if the Pacman is in the same position as the food, he can eat it
    if (pX == fX && pY == fY) {
        return 1;
    }
    //chack if the pacman could move up. The position should contain a '.' or 'C'.
    if  (pX >= 0 && (map[pX-1][pY] == '.' || map[pX-1][pY] == ' ' || map[pX-1][pY] == 'C') && checked[pX - 1][pY] == 0) { //
        //mark the position as checked
        checked[pX][pY] = 1;
        ate = canEat(l, c, map, checked, pX-1, pY, fX, fY);
        //mark off the position as checked
        checked[pX][pY] = 0;
        if (ate) {
            return 1;
        }
    }
    //chack if the pacman could move down. The position should contain a '.' or 'C'.
    if  (pX + 1 < l && (map[pX + 1][pY] == '.' || map[pX + 1][pY] == ' ' || map[pX + 1][pY] == 'C') && checked[pX + 1][pY] == 0) {
        checked[pX][pY] = 1;
        ate = canEat(l, c, map, checked, pX+1, pY, fX, fY);
        checked[pX][pY] = 0;
        if (ate) {
            return 1;
        }
    }
    //chack if the pacman could move left. The position should contain a '.' or 'C'.
    if  (pY - 1 >= 0 && (map[pX][pY - 1] == '.' || map[pX][pY - 1] == ' ' || map[pX][pY - 1] == 'C') && checked[pX][pY - 1] == 0) {
        checked[pX][pY] = 1;
        ate = canEat(l, c, map, checked, pX, pY-1, fX, fY);
        checked[pX][pY] = 0;
        if (ate) {
            return 1;
        }
    }
    //chack if the pacman could move right. The position should contain a '.' or 'C'.
    if  (pY + 1 < c && (map[pX][pY + 1] == '.' || map[pX][pY + 1] == ' ' || map[pX][pY + 1] == 'C') && checked[pX][pY + 1] == 0) {
        checked[pX][pY] = 1;
        ate = canEat(l, c, map, checked, pX, pY+1, fX, fY);
        checked[pX][pY] = 0;
        if (ate) {
            return 1;
        }
    }

    return 0;
}

//this function chack if each food is possible to eat by Pacman and mark it as ' ' if so and add 1 to the foodEaten counter
void pacman (int l, int c, char map[l][c], int pX, int pY, int *foodsEaten) {
    int fX = 0, fY = 0;
    int checked[l][c];

    //set all the positions to 0
    memset(checked, 0, sizeof(checked));
    
    /*
    printf("Mapa final:\n");
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < c; j++) {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
    */

    //check if the food is possible to eat by Pacman
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < c; j++) {
            if (map[i][j] == '.') {
                fX = i;
                fY = j;
                if (canEat(l, c, map, checked, pX, pY, fX, fY)) { //calling the recursive function
                    map[i][j] = ' ';
                    *foodsEaten = *foodsEaten + 1;
                }
            }
        }
    }

    //printing the map
    printf("Total de bolinhas devoradas: %d\n", *foodsEaten);
    printf("Mapa final:\n");
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < c; j++) {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
}

int main (void) {
    //declaring variables
    int l = 0, c = 0;
    int pX = 0, pY = 0, foodsEaten = 0;
    scanf("%d %d", &l, &c);
    char map[l][c];

    //initializing the matrix
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < c; j++) {
            scanf(" %c", &map[i][j]);
            if (map[i][j] == 'C') {
                pX = i;
                pY = j;
            }
        }
        getchar();
    }

    pacman(l, c, map, pX, pY, &foodsEaten);

    return 0;
}