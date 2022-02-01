#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_GAME_LEN 50

typedef enum SUIT {
    HEARTS = 3, //"♥" = 3
    DIAMONDS, //"♦" = 4
    CLUBS, //"♣" = 5
    SPADES//"♠" = 6
} Suit;

typedef struct CARD { //A card have a suit and a value
    int value;
    int suit;
} Card;

//handle with each card itself
Card handle_cards (char ccard[4]) {
    Card card;
    card.value = atoi(ccard);
    if (card.value == 0) {
        switch (ccard[0]) {
            case 'J':
                card.value = 11;
                break;
            case 'Q':
                card.value = 12;
                break;
            case 'K':
                card.value = 13;
                break;
            case 'A':
                card.value = 14;
                break;
            default:
            break;
        }
    }
    card.suit = ccard[strlen(ccard) - 1];

    return card;
}

// handle with entrys to improve the code
Card ** handle_entry (int ngames, char game[ngames][MAX_GAME_LEN], int ncards[ngames]) {
    char *ccard;
    Card ** cards = calloc(ngames, sizeof(Card*));
    
    for (int i = 0; i < ngames; i++) {
        cards[i] = calloc(1, sizeof(Card));
        ccard = strtok(game[i], " ");
        while (ccard != NULL) {
            cards[i] = realloc(cards[i], sizeof(Card) * (ncards[i] + 1));
            cards[i][ncards[i]] = handle_cards(ccard);
            ncards[i]++;
            ccard = strtok(NULL, " ");
        }
        //printf("\n");
    }

    return cards;
}

// print card
void print_card (Card card) {
    switch (card.value) {
        case 11:
            printf("J");
            break;
        case 12:
            printf("Q");
            break;
        case 13:
            printf("K");
            break;
        case 14:
            printf("A");
            break;
        default:
            printf("%d", card.value);
            break;
    }
    printf("%c ", card.suit);
}

//print the game  
void print_game (int ncards, Card cards[ncards]) {
    printf("Jogo [ ");
    for (int i = 0; i < ncards; i++) {
        print_card(cards[i]);
    }
    printf("]");
}

//Check if the games are valid and print the results
void check_games (int ngames, int ncards[ngames], Card ** cards) {
    int is_valid = 1;
    int joker_count = 0;
    Card joker = {0, 0};
    Card surrogate = {0, 0};
    if (ngames == 0) {
        printf("No games were played.\n");
        return;
    }
    for (int i = 0; i < ngames; i++) {
        print_game(ncards[i], cards[i]);
        if (ncards[i] < 3) {
            printf(" e invalido\n"); // é inválido
        } else {
            is_valid = 1;
            joker_count = 0;
            for (int j = 0; j < ncards[i]-1; j++) {
                if (cards[i][j].value+1 == cards[i][j+1].value && cards[i][j].suit == cards[i][j+1].suit) {
                    continue;
                } else if ( ((cards[i][j].value == 14 && cards[i][j+1].value == 2))&& cards[i][j].suit == cards[i][j+1].suit) {
                    continue;
                } else if ((cards[i][j].value == 2 || cards[i][j+1].value == 2) && joker_count < 2) {
                    //printf("entrou nessa opcao %d %d  ", cards[i][j].value, cards[i][j+1].value);
                    joker_count++;
                    if (cards[i][j].value == 2) {
                        joker = cards[i][j];
                        surrogate.value = cards[i][j+1].value-1;
                        surrogate.suit = cards[i][j+1].suit;
                    } else {
                        joker = cards[i][j+1];
                        surrogate.value = cards[i][j].value+1;
                        surrogate.suit = cards[i][j].suit;
                    }
                    continue;
                } else {
                    /*
                    //printf("%d%c, %d%c", cards[i][j].value, cards[i][j].suit, cards[i][j+1].value, cards[i][j+1].suit);
                    printf(" ");
                    print_card(cards[i][j]);
                    printf(", ");
                    print_card(cards[i][j+1]);
                    */
                    is_valid = 0;
                    break;
                }
            }
            if (is_valid) {
                if (joker_count == 0) printf(" e valido\n");  // é válido
                else {
                    printf(" e valido, ");  // é válido
                    print_card(joker);
                    printf(" no lugar de ");
                    print_card(surrogate);
                    printf("\n");
                }
            }
            else printf(" e invalido\n"); // é inválido
        }
    }

}

int main (void) {

    //Create the variables
    int ngames = 0;
    Card ** cards = NULL;
    scanf("%d\n", &ngames);
    int ncards[ngames];
    char games[ngames][MAX_GAME_LEN];

    //Read the games and initialize the variables
    for (int i = 0; i < ngames; i++) {
        fgets(games[i], MAX_GAME_LEN+1, stdin);
        games[i][strlen(games[i]) - 3] = '\0';
        memmove(&games[i][0], &games[i][2], strlen(games[i]));
    }
    for (int i = 0; i < ngames; i++) ncards[i] = 0;
    cards = handle_entry(ngames, games, ncards);

    /*
    //Print the cards //test
    for (int i = 0; i < ngames; i++) {
        for (int j = 0; j < ncards[i]; j++) {
            print_card(cards[i][j]);
            printf(" ");
        }
        printf("\n");
    }
    printf("\n\n\n\n");
    */
    /*
    printf("\u2660 \u2661 \u2662 \u2663 \u2664 \u2665 \u2666 \u2667\n");
    char * str = "♠";
    printf("LEN: %d\n", strlen(str));
    printf("EQ: %d\n", strcmp(str,"♠") == 0);
    printf("EQ: %d\n", strcmp(str,"\u2660") == 0);
    */

    //Check if the games are valid and print the results
    check_games(ngames, ncards, cards);

    //Free the memory
    for (int i = 0; i < ngames; i++) free(cards[i]);
    free(cards);
    return 0;
}