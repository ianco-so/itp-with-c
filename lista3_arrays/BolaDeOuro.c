#include <stdio.h>
#include <stdlib.h>

int main (void) {
    int nBettors, ballon_dOr;;
    scanf("%d", &nBettors);
    int bets[nBettors][2];
    for (int i = 0; i < nBettors; i++)  scanf("%d %d", &bets[i][0], &bets[i][1]);
    scanf("%d", &ballon_dOr);

    int winnersBalance = 0;
    int totalBalance = 0;
    int payout = 0;
    int totalPayout = 0;

    for (int i = 0; i < nBettors; i++) {
        totalBalance += bets[i][0];
        if (bets[i][1] == ballon_dOr)   winnersBalance += bets[i][0];
    }
    printf("Total: R$ %d \n", totalBalance);
    for (int i = 0; i < nBettors; i++) {
        if (winnersBalance > 0) {
            if (bets[i][1] == ballon_dOr) {
                payout = (int)(((double)(bets[i][0]))/winnersBalance * totalBalance *0.90);
                totalPayout += payout;
                printf("Apostador %d: R$ %i\n",i+1, payout);
            }
        } else {
            payout = (int)(((double)(bets[i][0]))/totalBalance * totalBalance *0.90);
            totalPayout += payout;
            printf("Apostador %d: R$ %i\n", i+1, payout);
        }
    }
    printf("Bebidas e petiscos: R$ %d", (int)(totalBalance-totalPayout));
    return 0;
}