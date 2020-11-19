#include <iostream>
#include "StateParser.h"
#define COLOR_MAX_LENGTH 8
int compare(const char a[], const char b[]){
    for(int i=0;a[i]!='\0';i++){
        if(a[i]!=b[i])
            return 0;
    }
    return 1;
}
int getColorFromName(char* name){
    if(compare(name, "green") != 0)
        return GREEN;
    if(compare(name, "blue") != 0)
        return BLUE;
    if(compare(name, "red") != 0)
        return RED;
    if(compare(name, "violet") != 0)
        return VIOLET;
    if(compare(name, "yellow") != 0)
        return YELLOW;
    if(compare(name, "white") != 0)
        return WHITE;
    if(compare(name, "black") != 0)
        return BLACK;
    return -1;
}
int loadLine(int i, Card deck[MAX_PLAYERS][MAX_CARDS_ON_HAND]){
    int cards = 0;
    while(true){
        int value;
        char color[COLOR_MAX_LENGTH];
        if(!(std::cin>>value))break;
        if(!(std::cin>>color))break;

        if(compare(color,"player") != 0) {
            break;
        }
        if(getColorFromName(color)==-1)break;
        deck[i][cards++]={value, getColorFromName(color)};
    }
    return cards;
}
int getColorCount(int colorId, Card cardsOnHand[MAX_PLAYERS][MAX_CARDS_ON_HAND], Card cardsInDeck[MAX_PLAYERS][MAX_CARDS_ON_HAND], int players, const int* cardsGiven, const int* cardsOnHold){
    int count = 0;
    for(int i = 0; i < players; i++){
        for(int j = 0; j < cardsGiven[i];j++){
            if(cardsOnHand[i][j].color==colorId){
                count++;
            }
        }
        for(int j = 0; j < cardsOnHold[i];j++){
            if(cardsInDeck[i][j].color==colorId){
                count++;
            }
        }
    }

    return count;
}
int getCrucibleCount(Card cardsOnHand[MAX_PLAYERS][MAX_CARDS_ON_HAND], Card cardsInDeck[MAX_PLAYERS][MAX_CARDS_ON_HAND], int players, const int* cardsGiven, const int* cardsOnHold){
    int uniqueColors = 0;
    for(int i = 1; i < COLORS; i++){
        if(getColorCount(i, cardsOnHand, cardsInDeck, players, cardsGiven, cardsOnHold)>0)
            uniqueColors++;
    }
    return uniqueColors;
}
GameState StateParser::ReadFromStream() {
    int playersNumber;
    int activePlayer;
    int explosionThreshold;
    char discard[32];
    std::cin>>discard>>discard>>discard>>activePlayer;
    std::cin>>discard>>discard>>discard>>playersNumber;
    std::cin>>discard>>discard>>discard>>explosionThreshold;
    Card cardsOnHand[MAX_PLAYERS][MAX_CARDS_ON_HAND];
    Card cardsInDeck[MAX_PLAYERS][MAX_CARDS_ON_HAND];
    int cardsGiven[MAX_PLAYERS] = {};
    int cardsOnHold[MAX_PLAYERS] = {};
    for(int i = 0; i < playersNumber;i++){
        std::cin>>discard>>discard;

        if(i==0){
            std::cin>>discard>>discard;
        }
        cardsGiven[i] = loadLine(i, cardsOnHand);
        std::cin>>discard>>discard;
        cardsOnHold[i] = loadLine(i, cardsInDeck);
    }
    Card cardsOnPiles[MAX_PILES][MAX_CARDS_ON_HAND];
    int numberCardOnPiles[MAX_PILES];
    int piles = getCrucibleCount(cardsOnHand, cardsInDeck, playersNumber, cardsGiven, cardsOnHold);
    for(int i = 0; i < piles; i++){
        std::cin>>discard;
        numberCardOnPiles[i]=loadLine(i,cardsOnPiles);
    }
    Settings settings{
        playersNumber,
        piles,
        0,
        0,
        0,
        0,
        explosionThreshold,
        activePlayer
    };
    return GameState(settings, cardsOnHand, cardsInDeck, cardsOnPiles, cardsGiven, cardsOnHold, numberCardOnPiles);
}