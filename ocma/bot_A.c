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

#include "definitions.h"
#include "io.h"
#include "localizationA.h"

int main() {
  char line[MAX_STR];   // temporarily data
  char *action;      // action to be taken
  int nBots;        
  Bot *bots;
  MyBot myBot;
  Position goalPosition;

  setbuf(stdin, NULL);   // stdin, stdout and stderr are unbuffered, so nothing is keeping momentarily
  setbuf(stdout, NULL);
  setbuf(stderr, NULL);

  // === START OF THE GAME ===
  int h, w; // height and width of the fishing area
  scanf("AREA %i %i", &h, &w);
  int fishingArea[h][w];
  int **overlappedFishingArea = NULL;
  scanf(" ID %s", myBot.bot.id); // the ' ' is necessary to read the '\n' of the previous line

  // === TURNS === 
  while (1) {
    memset(fishingArea, 0, sizeof(fishingArea)); // reset the fishing area

    // read the fishing area and the bots
    bots = ReadData(h, w, fishingArea, &nBots);

    // find myBot in the list of bots (mainly the position)
    for (int i = 0; i < nBots; i++) {
      if (strcmp(bots[i].id, myBot.bot.id) == 0) {
        strcpy(myBot.bot.id, bots[i].id);
        myBot.bot.position = bots[i].position;
        break;
      }
    }
    // insert a logic to be executed each turn
    overlappedFishingArea = OverlapFishingArea(h, w, fishingArea, nBots, bots, myBot.bot.position);
    if (myBot.weight < 10) {
      goalPosition = FindCloserFishingSpot(h, w, overlappedFishingArea, myBot.bot.position);
      if (goalPosition.x == myBot.bot.position.x && goalPosition.y == myBot.bot.position.y) {
        action ="FISH";
      } else {
        action = findPath(h, w, overlappedFishingArea, myBot.bot.position, goalPosition);
      }
    } else {
      goalPosition = FindCloserPort(h, w, overlappedFishingArea, myBot.bot.position);
      if (goalPosition.x == myBot.bot.position.x && goalPosition.y == myBot.bot.position.y) {
        action = "SELL";
      } else  {
        action = findPath(h, w, overlappedFishingArea, myBot.bot.position, goalPosition);
      }
    }
    printf("%s\n",action);

    // read the response of the action of the bot and update his status (if necessary)
    scanf("%s", line);
    if (isNumber(line) && atoi(line) != 0){
      myBot.weight = 0;
    } else if (strcmp(line, "MULLET") == 0 || strcmp(line, "SNAPPER") == 0 || strcmp(line, "SEABASS") == 0) myBot.weight++;
  }

  return 0;
}