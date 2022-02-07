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
//MULLET (Tainha): R$ 100.00/Kg (10 <= x < 20)
//SNAPPER (Cioba): R$ 150.00/Kg (20 <= x < 30)
//SEABASS (Robalo): R$ 200.00/Kg (30 <= x < 40)

typedef enum FishPrice {
  MULLET = 100,
  SNAPPER = 150,
  SEABASS = 200
} fPrice;

typedef struct POSITION {
  int x, y;
} Position;

typedef struct PLAYER {
  char id[MAX_STR];
  Position position;
} Bot;
 
Bot * readData(int h, int w, int fishingArea[h][w], int *nBots) {
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

int priceOfFish(int x) { // return the price of the fish x
  switch (x) {
    case 1: return MULLET; break;
    case 2: return SNAPPER; break;
    case 3: return SEABASS; break;
    default: return 0; break;
  }
}
Position findCloserFishingSpot (int h, int w, int nEnemies, int fishingArea[h][w], Bot enemies[nEnemies], Position currentPosition) {
  Position closerFishingSpot = currentPosition;
  int copiedFishingArea[h][w];

  //copy the fishing area
  for(int i = 0; i < h; i++) {
    for(int j = 0; j < w; j++) {
      copiedFishingArea[i][j] = fishingArea[i][j];
    }
  }
  //Overlap the copied fishing area with enemies positions
  for (int i = 0; i < nEnemies; i++) {
    copiedFishingArea[enemies[i].position.x][enemies[i].position.y] = -1;
  }
  //As the map was overlap on my bot's position and I don't want to lose the information, I return it now
  copiedFishingArea[currentPosition.x][currentPosition.y] = fishingArea[currentPosition.x][currentPosition.y];

  //Find the closer fishing spot
  int distance = 999999999; //arbitrary big number
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      //If the position is a fishing spot
      if (copiedFishingArea[i][j] > 11 && copiedFishingArea[i][j]%10 > 1) {
        //calculate the distance from the current position
        if (abs(currentPosition.x - i) + abs(currentPosition.y - j) < distance) { //If the distance of this fishing spot is smaller than the previous one
          distance = abs(currentPosition.x - i) + abs(currentPosition.y - j);
          //Save the closer fishing spot
          closerFishingSpot.x = i;
          closerFishingSpot.y = j;
        } else if (distance == abs(currentPosition.x - i) + abs(currentPosition.y - j)) { //If the distance of this fishing spot is equal to the previous one
          //find the better cost-benefit ratio
          int currentCostBenefitRatio = priceOfFish(copiedFishingArea[i][j]/10)* (copiedFishingArea[i][j]%10);
          int previousCostBenefitRatio = priceOfFish(copiedFishingArea[closerFishingSpot.x][closerFishingSpot.y]/10) * (copiedFishingArea[closerFishingSpot.x][closerFishingSpot.y]%10);
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
  int fishingArea[h][w];
  scanf(" ID %s", myBot.id); // the ' ' is necessary to read the '\n' of the previous line


  // use fprintf(strerr, "STUFF", var) for debug if necessary. Ex: fprintf(stderr, "Meu id = %s\n", myId);

  // === TURNS === 
  while (1) {
    memset(fishingArea, 0, sizeof(fishingArea)); // zera a área de pesca

    // LÊ OS DADOS DO JOGO E ATUALIZA OS DADOS DO BOT
    bots = readData(h, w, fishingArea, &nBots);

    prePosition = myBot.position;

    // find myBot in the list of bots (mainly the position)
    for (int i = 0; i < nBots; i++) {
      if (strcmp(bots[i].id, myBot.id) == 0) {
        strcpy(myBot.id, bots[i].id);
        myBot.position = bots[i].position;
        break;
      }
    }
    // insert a logic to be executed each turn
    Position goalPosition = findCloserFishingSpot(h, w, nBots, fishingArea, bots, myBot.position);
    // print the action to be executed
    printf("RIGHT\n");

    // read the response of the action of the bot and update his status (if necessary)
    scanf("%s", line);
  }

  return 0;
}