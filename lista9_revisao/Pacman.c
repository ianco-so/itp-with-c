#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//recursive function that return true if the Pacman could eat one certain food and false otherwise
int canEat(int l, int c, char map[l][c], int checked[l][c], int pacmanPosition[2], int foodPosition[2]) {
    int ate = 0;
    //base case: if the Pacman is in the same position as the food, he can eat it
    if (pacmanPosition[0] == foodPosition[0] && pacmanPosition[1] == foodPosition[1]) {
        return 1;
    }
    //chack if the pacman could move up. The position should contain a '.' or 'C'.
    if (pacmanPosition[0] - 1 >= 0 && (map[pacmanPosition[0] - 1][pacmanPosition[1]] == '.' || map[pacmanPosition[0] - 1][pacmanPosition[1]] == 'C') && checked[pacmanPosition[0] - 1][pacmanPosition[1]] == 0) {
        //mark the position as checked
        checked[pacmanPosition[0]][pacmanPosition[1]] = 1;
        ate = canEat(l, c, map, checked, pacmanPosition, foodPosition);
        //mark off the position as checked
        checked[pacmanPosition[0]][pacmanPosition[1]] = 0;
        if (ate) {
            return 1;
        }
    }
    //chack if the pacman could move down. The position should contain a '.' or 'C'.
    if (pacmanPosition[0] + 1 < l && (map[pacmanPosition[0] + 1][pacmanPosition[1]] == '.' || map[pacmanPosition[0] + 1][pacmanPosition[1]] == 'C') && checked[pacmanPosition[0] + 1][pacmanPosition[1]] == 0) {
        checked[pacmanPosition[0]][pacmanPosition[1]] = 1;
        ate = canEat(l, c, map, checked, pacmanPosition, foodPosition);
        checked[pacmanPosition[0]][pacmanPosition[1]] = 0;
        if (ate) {
            return 1;
        }
    }
    //chack if the pacman could move left. The position should contain a '.' or 'C'.
    if (pacmanPosition[1] - 1 >= 0 && (map[pacmanPosition[0]][pacmanPosition[1] - 1] == '.' || map[pacmanPosition[0]][pacmanPosition[1] - 1] == 'C') && checked[pacmanPosition[0]][pacmanPosition[1] - 1] == 0) {
        checked[pacmanPosition[0]][pacmanPosition[1]] = 1;
        ate = canEat(l, c, map, checked, pacmanPosition, foodPosition);
        checked[pacmanPosition[0]][pacmanPosition[1]] = 0;
        if (ate) {
            return 1;
        }
    }
    //chack if the pacman could move right. The position should contain a '.' or 'C'.
    if (pacmanPosition[1] + 1 < c && (map[pacmanPosition[0]][pacmanPosition[1] + 1] == '.' || map[pacmanPosition[0]][pacmanPosition[1] + 1] == 'C') && checked[pacmanPosition[0]][pacmanPosition[1] + 1] == 0) {
        checked[pacmanPosition[0]][pacmanPosition[1]] = 1;
        ate = canEat(l, c, map, checked, pacmanPosition, foodPosition);
        checked[pacmanPosition[0]][pacmanPosition[1]] = 0;
        if (ate) {
            return 1;
        }
    }
    return 0;
}

//this function chack if each food is possible to eat by Pacman and mark it as ' ' if so and add 1 to the foodEaten counter
int ** pacman (int l, int c, char map[l][c], int ** foodsEatenPositions, int pacmanPosition[2], int *foodsEaten) {
    int foodPosition[2] = {0,0};
    int checked[l][c];

    //set all the positions to 0
    memset(checked, 0, sizeof(checked));

    //check if the food is possible to eat by Pacman
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < c; j++) {
            if (map[i][j] == '.') {
                foodPosition[0] = i;
                foodPosition[1] = j;
                if (canEat(i, j, map, checked, pacmanPosition, foodPosition)) {
                    foodsEatenPositions[i][j] = 1;
                    (*foodsEaten)++;
                }
            }
        }
    }
    return foodsEatenPositions;
}

int main (void) {
    //declaring variables
    int l = 0, c = 0;
    int **foodsEatenPositions = NULL, pacmanPosition[2] = {0,0}, foodsEaten = 0;
    scanf("%d %d", &l, &c);
    char map[l][c];

    //initializing the food eaten positions array with 0
    foodsEatenPositions = (int **) calloc(l, sizeof(int *));
    for (int i = 0; i < l; i++) {
        foodsEatenPositions[i] = (int *) calloc(c, sizeof(int));
    }
    //initializing the matrix
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < c; j++) {
            scanf(" %c", &map[i][j]);
            if (map[i][j] == 'C') {
                pacmanPosition[0] = i;
                pacmanPosition[1] = j;
            }
        }
    }

    //calling the recursive function
    foodsEatenPositions = pacman(l, c, map, foodsEatenPositions, pacmanPosition, &foodsEaten);

    //printing the map
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < c; j++) {
            if (foodsEatenPositions[i][j] == 1) {
                printf("%c", map[i][j]);
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }

    return 0;
}