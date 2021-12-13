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

int * sort (int M, int N, int seed) {
    int *arr = (int *) calloc(N, sizeof(int));
    int count = 0, num = 0;
    bool has = false;

    srand(seed);
    do {
        num = rand() % M;
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
    } while (count < N);
    return arr;
}
void mark_card(Card card, int N, int sorted[N]) {
    for (int i = 0; i < N; i++) {
        if (card.nums[i] == sorted[i]) {
            card.mark[i] = 1;
        } else {
            card.mark[i] = 0;
        }
    }
}

int check_champ (Card card, int N) {
    for (int i = 0; i < N; i++) {
        if (card.mark[i] == 0) return 0;
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
    int champ = 0;
    Card *cards;
    char line[16] = {0};

    scanf("%d %d %d", &N, &M, &S);
    getchar();
    sorted = sort(M, N, S);

    cards = (Card *) calloc(1, sizeof(Card));
    fgets(line, 16, stdin);

    while(strcmp(line, "Comecou o jogo!") != 0) {
        int T = atoi(line);
        init_card(cards, T, N, M, n_players-1);
        cards = (Card *) realloc(cards, sizeof(Card) * (n_players + 1));
        mark_card(cards[n_players-1], N, sorted);
        n_players++;
        fgets(line, 16, stdin);
    }
    n_players--;

    for (int i = 0; i < n_players; i++) {
        if (check_champ(cards[i], N)) {
            champ = cards[i].id_card;
            break;
        }
    }
    for (int i = 0; i < N; i ++) {
        printf("%d ", sorted[i]);
    }
    printf("\n");
    printf("Bingo! Cartela %d: ", champ);
    for (int i = 0; i < cards[champ].N; i++) {
        printf("%d ", cards[champ].nums[i]);
    }
    return 0;
}