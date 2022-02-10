#include <stdio.h>
#include <stdlib.h>

#include "definitions.h"


int ** OverlapFishingArea(int h, int w, int fishingArea[h][w], int nBots, Bot bots[nBots], Position myPosition) {
  // create the matrix of the overlap
  int **overlappedFishingArea = malloc(h * sizeof(int *));
  for (int i = 0; i < h; i++) overlappedFishingArea[i] = malloc(w * sizeof(int));

  //copy the fishing area
  for(int i = 0; i < h; i++)  for(int j = 0; j < w; j++)  overlappedFishingArea[i][j] = fishingArea[i][j];

  //Overlap the copied fishing area with enemies positions
  for (int i = 0; i < nBots; i++) {
    if (overlappedFishingArea[bots[i].position.x][bots[i].position.y] != 1) {
      overlappedFishingArea[bots[i].position.x][bots[i].position.y] = -1;
    }
    
  }
  //As the map was overlap on my bot's position and I don't want to lose the information, I return it now
  overlappedFishingArea[myPosition.x][myPosition.y] = fishingArea[myPosition.x][myPosition.y];

  return overlappedFishingArea;
}

Bot * ReadData(int h, int w, int fishingArea[h][w], int *nBots) {
  char id[MAX_STR];
  int n;

  // read the fishing area
  for (int i = 0; i < h; i++) {   
    for (int j = 0; j < w; j++) {
      scanf("%i", &fishingArea[i][j]);
    }
  }

  // read the data of the players
  scanf(" BOTS %i", &n); // The ' ' is for the '\n' of the previous line
  *nBots = n; 
  Bot *bots = malloc(n * sizeof(Bot));
  for (int i = 0; i < n; i++) {
    scanf("%s %i %i", bots[i].id, &bots[i].position.x, &bots[i].position.y);
  }
  return bots;
}

int isNumber(char *line) {
  int i = 0;
  while (line[i] != '\0') {
    if (line[i] < '0' || line[i] > '9' || line[i] == '-' || line[i] == '.') return 0;
    i++;
  }
  return 1;
}