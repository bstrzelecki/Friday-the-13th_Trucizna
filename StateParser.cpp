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
        return 0;
    if(compare(name, "blue") != 0)
        return 1;
    if(compare(name, "red") != 0)
        return 2;
    if(compare(name, "violet") != 0)
        return 3;
    if(compare(name, "yellow") != 0)
        return 4;
    if(compare(name, "white") != 0)
        return 5;
    if(compare(name, "black") != 0)
        return 6;
    return -1;
}
int loadLine(int i, Card deck[MAX_PLAYERS][MAX_CARDS_ON_HAND]){
    int cards = 0;
    while(true){
        int value;
        char color[COLOR_MAX_LENGTH];
        if(!(std::cin>>value))break;
        if(!(std::cin>>color))break;
        int isValid = 0;
        if(compare(color,"player") != 0) {
            break;
        }
        for(auto c : colors){
            if(compare(color,c) == 0){
                isValid = 1;
                break;
            }
        }
        if(!isValid) {
            break;
        }
        deck[i][cards++]={value, getColorFromName(color)};
    }
    return cards;
}
GameState StateParser::ReadFromStream() {
    int playersNumber;
    int activePlayer;
    char discard[32];
    std::cin>>discard>>discard>>discard>>activePlayer;
    std::cin>>discard>>discard>>discard>>playersNumber;
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
    return GameState(playersNumber, cardsOnHand, cardsInDeck, cardsGiven, cardsOnHold);
}