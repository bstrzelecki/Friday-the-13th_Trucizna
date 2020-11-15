#ifndef definitions
#define definitions

#define GREEN 0
#define BLUE 1
#define RED 2
#define VIOLET 3
#define YELLOW 4
#define WHITE 5
#define BLACK 6


inline const char* colors[] = {
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
}Card;

typedef struct {
    int crucibles;
    int greenCards;
    int greenCardValue;
    int cardCount;
    int totalCards;
}Settings;

#endif