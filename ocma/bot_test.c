/********************************************************************
bot_A
  
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

int FishPricing(int x) { // return the price of the fish x
  switch (x) {
    case 1: return MULLET; break;
    case 2: return SNAPPER; break;
    case 3: return SEABASS; break;
    default: return 0; break;
  }
}

int ** OverlapFishingArea(int h, int w, int fishingArea[h][w], int nBots, Bot bots[nBots], Position myPosition) {
  // create the matrix of the overlap
  int **overlapFishingArea = malloc(h * sizeof(int *));
  for (int i = 0; i < h; i++) overlapFishingArea[i] = malloc(w * sizeof(int));

  //copy the fishing area
  for(int i = 0; i < h; i++)  for(int j = 0; j < w; j++)  overlapFishingArea[i][j] = fishingArea[i][j];

  //Overlap the copied fishing area with enemies positions
  for (int i = 0; i < nBots; i++)  overlapFishingArea[bots[i].position.x][bots[i].position.y] = -1;

  //As the map was overlap on my bot's position and I don't want to lose the information, I return it now
  overlapFishingArea[myPosition.x][myPosition.y] = fishingArea[myPosition.x][myPosition.y];

  return overlapFishingArea;
}

Position FindCloserFishingSpot (int h, int w, int **overlapedFishingArea, Position myPosition) {
  Position closerFishingSpot = myPosition;

  //Find the closer fishing spot
  int distance = 999999999; //arbitrary big number
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      //If the position is a fishing spot
      if (overlapedFishingArea[i][j] > 11 &&  overlapedFishingArea[i][j]%10 > 1) {
        //calculate the distance from the current position
        if (abs(myPosition.x - i) + abs(myPosition.y - j) < distance) { //If the distance of this fishing spot is smaller than the previous one
          distance = abs(myPosition.x - i) + abs(myPosition.y - j);
          //Save the closer fishing spot
          closerFishingSpot.x = i;
          closerFishingSpot.y = j;
        } else if (distance == abs(myPosition.x - i) + abs(myPosition.y - j)) { //If the distance of this fishing spot is equal to the previous one
          //find the better cost-benefit ratio
          int currentCostBenefitRatio = FishPricing(overlapedFishingArea[i][j]/10)* (overlapedFishingArea[i][j]%10);
          int previousCostBenefitRatio = FishPricing(overlapedFishingArea[closerFishingSpot.x][closerFishingSpot.y]/10) * (overlapedFishingArea[closerFishingSpot.x][closerFishingSpot.y]%10);
          if (currentCostBenefitRatio > previousCostBenefitRatio) {
            //Save the closer fishing spot with the better cost-benefit ratio
            closerFishingSpot.x = i;
            closerFishingSpot.y = j;
          }
        }
      }
    }
  }

  return closerFishingSpot; //if there is no closer fishing spot, the current position will be returned
}

int main() {
  char line[MAX_STR];   // temporarily data
  //char myId[MAX_STR]; 
  int nBots;        
  Bot *bots, myBot;
  Position prePosition; // previous position of myBot

  setbuf(stdin, NULL);   // stdin, stdout and stderr are unbuffered, so nothing is keeping momentarily
  setbuf(stdout, NULL);
  setbuf(stderr, NULL);

  // === START OF THE GAME ===
  int h, w; // height and width of the fishing area
  scanf("AREA %i %i", &h, &w);
  printf("AREA %i %i\n", h, w);
  int fishingArea[h][w];
  int **overlapedFishingArea = NULL;
  scanf(" ID %s", myBot.id); // the ' ' is necessary to read the '\n' of the previous line


  // use fprintf(strerr, "STUFF", var) for debug if necessary. Ex: fprintf(stderr, "Meu id = %s\n", myId);

  // === TURNS === 
  while (1) {
    memset(fishingArea, 0, sizeof(fishingArea)); // zera a área de pesca

    // LÊ OS DADOS DO JOGO E ATUALIZA OS DADOS DO BOT
    bots = ReadData(h, w, fishingArea, &nBots);

    prePosition = myBot.position;

    // find myBot in the list of bots (mainly the position)
    for (int i = 0; i < nBots; i++) {
      if (strcmp(bots[i].id, myBot.id) == 0) {
        strcpy(myBot.id, bots[i].id);
        myBot.position = bots[i].position;
        break;
      }
    }
    // print the position of myBot
    printf("POSITION %i %i\n", myBot.position.x, myBot.position.y);
    // insert a logic to be executed each turn
    overlapedFishingArea = OverlapFishingArea(h, w, fishingArea, nBots, bots, myBot.position);

    
    // print the overlapedFishingArea
    for (int i = 0; i < h; i++) {
      printf("%i|", i);
      for (int j = 0; j < w; j++) {
        printf("%i ", overlapedFishingArea[i][j]);
      }
      printf("\n");
    }
    

    Position goalPosition = FindCloserFishingSpot(h, w, overlapedFishingArea, myBot.position);
    printf("goalPosition = (%i, %i)\n", goalPosition.x, goalPosition.y);
    // print the action to be executed
    printf("RIGHT\n");

    // read the response of the action of the bot and update his status (if necessary)
    scanf("%s", line);
  }

  return 0;
}