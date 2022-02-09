#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "definitions.h"

int FishPricing(int x) { // return the price of the fish x
  switch (x) {
    case 1: return MULLET; break;
    case 2: return SNAPPER; break;
    case 3: return SEABASS; break;
    default: return 0; break;
  }
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

Position FindMostProfFishingSpot (int h, int w, int **overlappedFishingArea, Position myPosition) {
  Position mostProfFishingSpot = myPosition;
  int expectedProfit = 0; //arbitrary small number
  int distance = 999999999; //arbitrary big number
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
        if (overlappedFishingArea[i][j] > 11 &&  overlappedFishingArea[i][j]%10 > 1) { //If is a valid fishing spot
            if (expectedProfit < FishPricing(overlappedFishingArea[i][j]/10) * (overlappedFishingArea[i][j]%10)) {
                expectedProfit = FishPricing(overlappedFishingArea[i][j]/10) * (overlappedFishingArea[i][j]%10);
                distance = abs(myPosition.x - i) + abs(myPosition.y - j);
                mostProfFishingSpot.x = i;
                mostProfFishingSpot.y = j;
            } else if (expectedProfit == FishPricing(overlappedFishingArea[i][j]/10) * (overlappedFishingArea[i][j]%10)) { //If the expected profit is equal to the previous one
                if (abs(myPosition.x - i) + abs(myPosition.y - j) < distance) {//Then we check the closest distance
                    distance = abs(myPosition.x - i) + abs(myPosition.y - j); 
                    mostProfFishingSpot.x = i;
                    mostProfFishingSpot.y = j;
                }
            }
        }
    }
  }
  return mostProfFishingSpot;
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