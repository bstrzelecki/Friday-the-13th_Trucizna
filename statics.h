#ifndef definitions
#define definitions

#define MAX_PLAYERS 20
#define MAX_CARDS_ON_HAND 70
#define MAX_PILES 6
#define COLORS 7
#define MAX_VALUE 30

#define VALIDATION_ERROR 0
#define VALIDATION_SUCCESS 1

#define VALIDATION_RESULT int
#define COLOR int
#define GREEN 0
#define BLUE 1
#define RED 2
#define VIOLET 3
#define YELLOW 4
#define WHITE 5

#define BLACK 6

#define MEMTEST(x) if((x)==nullptr){printf("MEMORY ERROR");}

inline const char* const colors[] = {
        "green",
        "blue",
        "red",
        "violet",
        "yellow",
        "white",
        "black"
};
typedef struct {
    int value;
    int color;
} Card;

typedef struct {
    int players;
    int crucibles;
    int greenCards;
    int greenCardValue;
    int cardCount;
    int totalCards;
    int explosionThreshold;
    int activePlayer;
    int games;
} Settings;

#endif