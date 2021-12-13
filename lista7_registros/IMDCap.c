#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


typedef struct card{
    int id_card;
    int N;
    int *nums;
    int *mark;
} Card;

int * sort (int M, int len, int seed) {
    int *arr = (int *) calloc(len, sizeof(int));
    int count = 0, num = 0;
    bool has = false;

    srand(seed);
    do {
        num = rand() % M;
        num += 1;
        has = false;
        for (int i = 0; i < count; i++) {
            if (arr[i] == num) {
                has = true;
                break;
            }
        }
        if (!has) {
            arr[count] = num;
            count++;
        }
    } while (count < len);
    return arr;
}
void mark_card(Card card, int last_sorted) {
    for (int i = 0; i < card.N; i++) {
        if (card.nums[i] == last_sorted) {
            card.mark[i] = 1;
        }
    }
}

int check_champ (Card card) {
    for (int i = 0; i < card.N; i++) {
        if (card.mark[i] == 0) {
            return 0;
        }
    }
    return 1;
}

void init_card(Card *card, int T, int N, int M, int i) {
    card[i].id_card = T;
    card[i].N = N;
    card[i].nums = sort(M, N, T);
    card[i].mark = (int *) calloc(N, sizeof(int));   
}

int main (void) {
    int M = 0, N = 0, S = 0, n_players = 1;
    int * sorted;
    Card champ;
    int len_sorted_arr = 0;
    Card *cards;
    char line[16] = {0};

    scanf("%d %d %d", &N, &M, &S);
    getchar();

    cards = (Card *) calloc(1, sizeof(Card));
    fgets(line, 16, stdin);
    //inicilizer all cards
    while(strcmp(line, "Comecou o jogo!") != 0) {
        int T = atoi(line);
        init_card(cards, T, N, M, n_players-1);
        cards = (Card *) realloc(cards, sizeof(Card) * (n_players + 1));
        n_players++;
        fgets(line, 16, stdin);
    }
    n_players--;
    //lets play
    bool stop = false;
    do {
        len_sorted_arr++;
        sorted = sort(M, len_sorted_arr , S);
        for (int i = 0; i < n_players; i++) {
            mark_card(cards[i], sorted[len_sorted_arr - 1]);
            if(check_champ(cards[i])) {
                champ = cards[i];
                stop = true;
                break;
            }
        }
    } while (len_sorted_arr < M && !stop);
    //for the future
    for (int i = 0; i < len_sorted_arr; i ++) {
        printf("%d ", sorted[i]);
    }
    printf("\n");
    printf("Bingo! Cartela %d: ", champ.id_card);
    for (int i = 0; i < n_players; i++) {
        if (cards[i].id_card == champ.id_card) {
            for (int j = 0; j < N; j++) {
                printf("%d ", cards[i].nums[j]);
            }
            break;
        }
    }
    return 0;
}