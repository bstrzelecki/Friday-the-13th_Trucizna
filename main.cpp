#include <iostream>

#define GREEN 0
#define BLUE 1
#define RED 2
#define VIOLET 3
#define YELLOW 4
#define WHITE 5
#define BLACK 6
const char* colors[] = {
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
}
Card;
void displayCard(Card card){
    std::cout<<card.value << " ";
    std::cout<<colors[card.color]<<" ";
}

void displayDeck(Card* deck, int count){
    for(int i = 0; i < count; i++){
        displayCard(deck[i]);
    }
}

void sort(int* array, int length){
    auto swap = [](int* a, int* b){
        int t = *a;
        *a = *b;
        *b = t;
    };

    for(int i = 0; i < length - 1; i++){
        for(int j = 0; j < length - i - j; j++){
            if(array[j]>array[j + 1]){
                swap(&(array[j]),&(array[j+1]));
            }
        }
    }
}

int main() {
    int k,g,gv,o;
    std::cin>>k>>g>>gv>>o;

    struct {
        int crucibles;
        int greenCards;
        int greenCardValue;
        int cardCount;
        int totalCards;
    }
    settings = {
        k,g,gv,o,g+k*o
    };
    Card* deck= new Card[settings.totalCards];

    for(int i = 0; i < settings.greenCards;i++){
        deck[i] = {settings.greenCardValue, GREEN};
    }
    int* values = new int[settings.cardCount];
    for(int i = 0; i < settings.cardCount; i++){
        int input;
        std::cin>>input;
        values[i] = input;
    }
    sort(values, settings.cardCount);

    int j = 0;
    int color = 1;
    for(int i = settings.greenCards; i < settings.totalCards; i++,j++){
        if(j >= settings.cardCount){
            color++;
            j = 0;
        }
        deck[i] = {values[j], color};
    }
    displayDeck(deck, settings.totalCards);
    delete [] values;
    delete [] deck;

    return 0;
}
