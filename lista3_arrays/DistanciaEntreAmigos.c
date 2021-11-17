#include <stdio.h>
#include <stdlib.h>

int maxDistance (int nBuildings, int buildingFloors[nBuildings]) {
    int maxDistance = 0;
    for (int i = 0; i < nBuildings; i++) {
        for (int j = 0; j < nBuildings; j++) {
            if (i != j) {
                int distance = buildingFloors[i] + buildingFloors[j] + abs(i - j);
                if (distance > maxDistance) maxDistance = distance;
            }
        }
    }
    return maxDistance;
}

int main (void) {
    int nBuildings;
    scanf("%d", &nBuildings);
    int buildingFloors[nBuildings];
    for (int i = 0; i < nBuildings; i++)    scanf("%d", &buildingFloors[i]);
    printf("%d", maxDistance(nBuildings, buildingFloors));
    return 0;
}