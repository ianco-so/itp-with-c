#ifndef MAX_STR
    #define MAX_STR 50
#endif

#ifndef DEF_FISH_PRICE
    #define DEF_FISH_PRICE
    typedef enum FishPrice {
        MULLET = 100, //MULLET (Tainha): R$ 100.00/Kg (10 <= x < 20)
        SNAPPER = 150, //SNAPPER (Cioba): R$ 150.00/Kg (20 <= x < 30)
        SEABASS = 200 //SEABASS (Robalo): R$ 200.00/Kg (30 <= x < 40)
    } FishPrice;
#endif

#ifndef DEF_POSITION
    #define DEF_POSITION
    typedef struct POSITION {
        int x, y;
    } Position;
#endif

#ifndef DEF_BOT
    #define DEF_BOT
    typedef struct BOT {
        char id[MAX_STR];
        Position position;
    } Bot;
#endif

#ifndef DEF_PLAYER
    #define DEF_PLAYER
    typedef struct PLAYER {
        Bot bot;
        int weight;
    }MyBot;
#endif