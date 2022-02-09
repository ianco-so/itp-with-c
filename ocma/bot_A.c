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

typedef struct PLAYER1 {
  Bot bot;
  int weight;
  float profit;
}MyBot;

int ** OverlapFishingArea(int h, int w, int fishingArea[h][w], int nBots, Bot bots[nBots], Position myPosition);
Bot * ReadData(int h, int w, int fishingArea[h][w], int *nBots);
char * findPath(int h, int w, int **overlappedFishingArea, Position myPosition, Position goalPosition);
int isNumber(char *line);
Position FindCloserPort (int h, int w, int **overlappedFishingArea, Position myPosition);
Position FindCloserFishingSpot (int h, int w, int **overlappedFishingArea, Position myPosition);
int FishPricing(int x);

int main() {
  char line[MAX_STR];   // temporarily data
  char *action;      // action to be taken
  int nBots;        
  Bot *bots;
  MyBot myBot;
  //Position prePosition; // previous position of myBot

  setbuf(stdin, NULL);   // stdin, stdout and stderr are unbuffered, so nothing is keeping momentarily
  setbuf(stdout, NULL);
  setbuf(stderr, NULL);

  // === START OF THE GAME ===
  int h, w; // height and width of the fishing area
  scanf("AREA %i %i", &h, &w);
  int fishingArea[h][w];
  int **overlappedFishingArea = NULL;
  scanf(" ID %s", myBot.bot.id); // the ' ' is necessary to read the '\n' of the previous line


  // use fprintf(strerr, "STUFF", var) for debug if necessary. Ex: fprintf(stderr, "Meu id = %s\n", myId);

  // === TURNS === 
  while (1) {
    memset(fishingArea, 0, sizeof(fishingArea)); // reset the fishing area

    // read the fishing area and the bots
    bots = ReadData(h, w, fishingArea, &nBots);

    //prePosition = myBot.bot.position;

    // find myBot in the list of bots (mainly the position)
    for (int i = 0; i < nBots; i++) {
      if (strcmp(bots[i].id, myBot.bot.id) == 0) {
        strcpy(myBot.bot.id, bots[i].id);
        myBot.bot.position = bots[i].position;
        break;
      }
    }
    fprintf(stderr, "Area: %ix%i - My ID: %s - My Position: %i %i  - Weight: %i\n", h, w, myBot.bot.id, myBot.bot.position.x, myBot.bot.position.y, myBot.weight);
    /*
    for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++) {
        fprintf(stderr, "%i ", fishingArea[i][j]);
      }
      fprintf(stderr, "\n");
    }
    */
    // insert a logic to be executed each turn
    overlappedFishingArea = OverlapFishingArea(h, w, fishingArea, nBots, bots, myBot.bot.position);
    if (myBot.weight < 10) {
      Position goalPosition = FindCloserFishingSpot(h, w, overlappedFishingArea, myBot.bot.position);
      if (goalPosition.x == myBot.bot.position.x && goalPosition.y == myBot.bot.position.y) {
        action ="FISH";
      } else {
        action = findPath(h, w, overlappedFishingArea, myBot.bot.position, goalPosition);
      }
    } else {
      Position goalPosition = FindCloserPort(h, w, overlappedFishingArea, myBot.bot.position);
      if (goalPosition.x == myBot.bot.position.x && goalPosition.y == myBot.bot.position.y) {
        action = "SELL";
      } else  {
        action = findPath(h, w, overlappedFishingArea, myBot.bot.position, goalPosition);
      }
    }
    fprintf(stderr, "Action: %s\n", action);
    printf("%s\n",action);

    // read the response of the action of the bot and update his status (if necessary)
    scanf("%s", line);
    fprintf(stderr, "RESPONSE %s\n", line);
    //check if line is a number, if it's, add it to the profit
    //if it's an fish, then add the fish to the weight of the boat
    //if it's an fine, then deduct the fine from the profit
    //If it's something else, then do nothing
    if (isNumber(line)){
      myBot.profit += atoi(line);
      myBot.weight == 0;
    } else if (strcmp(line, "MULLET") == 0 || strcmp(line, "SNAPPER") == 0 || strcmp(line, "SEABASS") == 0) myBot.weight++;
    else if (strcmp(line, "IMPACT") == 0) myBot.profit -= 5e4;
    else if (strcmp(line, "OUT") == 0)  myBot.profit -= 5e2;
    else if (strcmp(line, "DONE") == 0 || strcmp(line, "NONE") == 0 || strcmp(line, "BUSY") == 0) {}// do nothing kkkkkk
  }

  return 0;
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
Position FindCloserFishingSpot (int h, int w, int **overlappedFishingArea, Position myPosition) {
  Position closerFishingSpot = myPosition;

  //Find the closer fishing spot
  int distance = 999999999; //arbitrary big number
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      //If the position is a fishing spot
      if (overlappedFishingArea[i][j] > 11 &&  overlappedFishingArea[i][j]%10 > 1) {
        //calculate the distance from the current position
        if (abs(myPosition.x - i) + abs(myPosition.y - j) < distance) { //If the distance of this fishing spot is smaller than the previous one
          distance = abs(myPosition.x - i) + abs(myPosition.y - j);
          //Save the closer fishing spot
          closerFishingSpot.x = i;
          closerFishingSpot.y = j;
        } else if (distance == abs(myPosition.x - i) + abs(myPosition.y - j)) { //If the distance of this fishing spot is equal to the previous one
          //find the better cost-benefit ratio
          int currentCostBenefitRatio = FishPricing(overlappedFishingArea[i][j]/10)* (overlappedFishingArea[i][j]%10);
          int previousCostBenefitRatio = FishPricing(overlappedFishingArea[closerFishingSpot.x][closerFishingSpot.y]/10) * (overlappedFishingArea[closerFishingSpot.x][closerFishingSpot.y]%10);
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
int FishPricing(int x) { // return the price of the fish x
  switch (x) {
    case 1: return MULLET; break;
    case 2: return SNAPPER; break;
    case 3: return SEABASS; break;
    default: return 0; break;
  }
}