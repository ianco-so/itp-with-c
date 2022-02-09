/********************************************************************
bot_test.c
  
After receiving the initial information of the game, each round this
bot will find the best action to take and send it to the ocma.
The goal of this bot is to maximize the fishing profit keeping 
the environment safe
********************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STR 50



typedef enum FishPrice {
  MULLET = 100, //MULLET (Tainha): R$ 100.00/Kg (10 <= x < 20)
  SNAPPER = 150, //SNAPPER (Cioba): R$ 150.00/Kg (20 <= x < 30)
  SEABASS = 200 //SEABASS (Robalo): R$ 200.00/Kg (30 <= x < 40)
} FishPrice;

typedef struct POSITION {
  int x, y;
} Position;

typedef struct PLAYER {
  char id[MAX_STR];
  Position position;
} Bot;

typedef struct PLAYER1 {
  Bot bot;
  int weight;
  float profit;
}MyBot;

Bot * ReadData(int h, int w, int fishingArea[h][w], int *nBots, FILE *file);

int FishPricing(int x);

int ** OverlapFishingArea(int h, int w, int fishingArea[h][w], int nBots, Bot bots[nBots], Position myPosition);

Position FindCloserPort (int h, int w, int **overlappedFishingArea, Position myPosition);

int isNumber(char *line);

Position FindCloserFishingSpot (int h, int w, int **overlappedFishingArea, Position myPosition);

char * findPath(int h, int w, int **overlappedFishingArea, Position myPosition, Position goalPosition);

int main(void) {
  char line[MAX_STR];
  char *action;
  int nBots;        
  Bot *bots;
  MyBot myBot;
  Position prePosition;
  int h, w;

  // Read the initial information of the game
  FILE* file = fopen("Entry.txt", "r");
  if (file == NULL) {
    printf("Error opening file!\n");
  }

  fscanf(file, "AREA %i %i", &h, &w);
  printf("AREA: %ix%i\n", h, w);
  int fishingArea[h][w];
  int **overlappedFishingArea = NULL;
  fscanf(file, " ID %s", myBot.bot.id);
  int count = 0;
  while (count < 2) {
    memset(fishingArea, 0, sizeof(fishingArea));
    bots = ReadData(h, w, fishingArea, &nBots, file);

    //print fishing area and bots
    for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++) {
        printf("%i ", fishingArea[i][j]);
      }
      printf("\n");
    }
    for (int i = 0; i < nBots; i++) {
      printf("%s %i %i\n", bots[i].id, bots[i].position.x, bots[i].position.y);
    }
    //prePosition = myBot.bot.position;

    for (int i = 0; i < nBots; i++) {
      if (strcmp(bots[i].id, myBot.bot.id) == 0) {
        strcpy(myBot.bot.id, bots[i].id);
        myBot.bot.position = bots[i].position;
        break;
      }
    }

    printf("My ID: %s\n", myBot.bot.id);
    printf("My position: %i %i\n", myBot.bot.position.x, myBot.bot.position.y);

    overlappedFishingArea = OverlapFishingArea(h, w, fishingArea, nBots, bots, myBot.bot.position);
    if (myBot.weight < 10) {
      Position goalPosition = FindCloserFishingSpot(h, w, overlappedFishingArea, myBot.bot.position);
      printf("My goal position: %i %i\n", goalPosition.x, goalPosition.y);
      if (goalPosition.x == myBot.bot.position.x && goalPosition.y == myBot.bot.position.y) {
        action = "FISH";
        printf("ACTION: %s\n", action);
      } else {
        action = findPath(h, w, overlappedFishingArea, myBot.bot.position, goalPosition);
      }
    } else {
      Position goalPosition = FindCloserPort(h, w, overlappedFishingArea, myBot.bot.position);
      if (goalPosition.x == myBot.bot.position.x && goalPosition.y == myBot.bot.position.y) {
        action = "SELL";
        printf("ACTION: %s\n", action);
      } else {
        action = findPath(h, w, overlappedFishingArea, myBot.bot.position, goalPosition);
      }
    }
    
    printf("ACTION: %s\n", action);

    fscanf(file, "%s", line);

    if (isNumber(line)) myBot.profit += atoi(line);
    else if (strcmp(line, "MULLET") == 0 || strcmp(line, "SNAPPER") == 0 || strcmp(line, "SEABASS") == 0) myBot.weight++;
    else if (strcmp(line, "IMPACT") == 0) myBot.profit -= 5e4;
    else if (strcmp(line, "OUT") == 0)  myBot.profit -= 5e2;
    else if (strcmp(line, "DONE") == 0 || strcmp(line, "NONE") == 0 || strcmp(line, "BUSY") == 0) {}// do nothing kkkkkk
    count++;
  }
  count++;
  if (file != NULL) fclose(file);
  return 0;
}

char * findPath(int h, int w, int **overlappedFishingArea, Position myPosition, Position goalPosition) {
  if (myPosition.x > goalPosition.x) { //above
    if (overlappedFishingArea[myPosition.x - 1][myPosition.y] != -1)  return "UP"; //and there is no obstacle
    else if (myPosition.y == goalPosition.y){ //if there is obstacle, but the obstacle is in the same column (case the goal is not in the same column this will be treated in the next ifs)
      if (myPosition.y < w - 1) {
        if (overlappedFishingArea[myPosition.x][myPosition.y + 1] != -1) return "RIGHT";
        else return "UP";
      } else if (myPosition.y > 0) {
        if (overlappedFishingArea[myPosition.x][myPosition.y - 1] != -1) return "LEFT";
        else return "UP";
      } else return "STAY"; //All movements are blocked
    } 
  }
  if (myPosition.x < goalPosition.x) { //below
    if (overlappedFishingArea[myPosition.x + 1][myPosition.y] != -1)  return "DOWN";
    else if (myPosition.y == goalPosition.y){
      if (myPosition.y < w - 1) {
        if (overlappedFishingArea[myPosition.x][myPosition.y + 1] != -1) return "RIGHT";
        else return "DOWN";
      } else if (myPosition.y > 0) {
        if (overlappedFishingArea[myPosition.x][myPosition.y - 1] != -1) return "LEFT";
        else return "DOWN";
      } else return "STAY"; //All movements are blocked
    }
  }
  if (myPosition.y < goalPosition.y) { //right
    if (overlappedFishingArea[myPosition.x][myPosition.y + 1] != -1)  return "RIGHT"; //and there is no obstacle
    else if (myPosition.x < h - 1) {
      if (overlappedFishingArea[myPosition.x + 1][myPosition.y] != -1) return "DOWN";
      else return "STAY";
    } 
    else if (myPosition.x > 0) {
      if (overlappedFishingArea[myPosition.x - 1][myPosition.y] != -1) return "UP";
      else return "RIGHT";
    } else return "STAY"; //All movements are blocked
  }
  if (myPosition.y > goalPosition.y) { //left
    if (overlappedFishingArea[myPosition.x][myPosition.y - 1] != -1)  return "LEFT";
    else if (myPosition.x < h - 1) {
      if (overlappedFishingArea[myPosition.x + 1][myPosition.y] != -1) return "DOWN";
      else return "LEFT";
    }
    else if (myPosition.x > 0) {
      if (overlappedFishingArea[myPosition.x - 1][myPosition.y] != -1) return "UP";
      else return "LEFT";
    } else return "STAY"; //All movements are blocked
  }
  return "STAY";
}

Position FindCloserFishingSpot (int h, int w, int **overlappedFishingArea, Position myPosition) {
  Position closerFishingSpot = myPosition;

  int distance = 999999999;
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      if (overlappedFishingArea[i][j] > 11 &&  overlappedFishingArea[i][j]%10 > 1) {
        if (abs(myPosition.x - i) + abs(myPosition.y - j) < distance) {
          distance = abs(myPosition.x - i) + abs(myPosition.y - j);
          closerFishingSpot.x = i;
          closerFishingSpot.y = j;
        } else if (distance == abs(myPosition.x - i) + abs(myPosition.y - j)) {
          int currentCostBenefitRatio = FishPricing(overlappedFishingArea[i][j]/10)* (overlappedFishingArea[i][j]%10);
          int previousCostBenefitRatio = FishPricing(overlappedFishingArea[closerFishingSpot.x][closerFishingSpot.y]/10) * (overlappedFishingArea[closerFishingSpot.x][closerFishingSpot.y]%10);
          if (currentCostBenefitRatio > previousCostBenefitRatio) {
            closerFishingSpot.x = i;
            closerFishingSpot.y = j;
          }
        }
      }
    }
  }

  return closerFishingSpot; //if there is no closer fishing spot, the current position will be returned
}

int isNumber(char *line) {
  int i = 0;
  while (line[i] != '\0') {
    if (line[i] < '0' || line[i] > '9') return 0;
    i++;
  }
  return 1;
}

Position FindCloserPort (int h, int w, int **overlappedFishingArea, Position myPosition) {
  Position closerPort = myPosition;
  int distance = 999999999;
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      if (overlappedFishingArea[i][j] == 1) {
        if (abs(myPosition.x - i) + abs(myPosition.y - j) < distance) {
          distance = abs(myPosition.x - i) + abs(myPosition.y - j);
          closerPort.x = i;
          closerPort.y = j;
        }
      }
    }
  }

  return closerPort;
}

int ** OverlapFishingArea(int h, int w, int fishingArea[h][w], int nBots, Bot bots[nBots], Position myPosition) {
  int **overlapFishingArea = malloc(h * sizeof(int *));
  for (int i = 0; i < h; i++) overlapFishingArea[i] = malloc(w * sizeof(int));

  for(int i = 0; i < h; i++)  for(int j = 0; j < w; j++)  overlapFishingArea[i][j] = fishingArea[i][j];

  for (int i = 0; i < nBots; i++)  overlapFishingArea[bots[i].position.x][bots[i].position.y] = -1;

  overlapFishingArea[myPosition.x][myPosition.y] = fishingArea[myPosition.x][myPosition.y];

  return overlapFishingArea;
}

int FishPricing(int x) { 
  switch (x) {
    case 1: return MULLET; break;
    case 2: return SNAPPER; break;
    case 3: return SEABASS; break;
    default: return 0; break;
  }
}

Bot * ReadData(int h, int w, int fishingArea[h][w], int *nBots, FILE *file) {
  char id[MAX_STR];
  int n;

  for (int i = 0; i < h; i++) {   
    for (int j = 0; j < w; j++) {
      fscanf(file, "%i", &fishingArea[i][j]);
    }
  }

  fscanf(file, " BOTS %i", &n); 
  *nBots = n; 
  Bot *bots = malloc(n * sizeof(Bot));
  for (int i = 0; i < n; i++) {
    fscanf(file, "%s %i %i", bots[i].id, &bots[i].position.x, &bots[i].position.y);
  }
  return bots;
}