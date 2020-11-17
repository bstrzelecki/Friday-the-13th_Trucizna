#include <cstdlib>
#include <iostream>
#include "GameState.h"

GameState::GameState(Settings settings, Deck& deck) {
    activePlayer = 1;
    playersNumber = settings.players;
    piles = settings.crucibles;
    playerHand = (Deck*)std::malloc(sizeof(Deck)*playersNumber);
    playerDeck = (Deck*)std::malloc(sizeof(Deck)*playersNumber);
    pileDeck = (Deck*)std::malloc(sizeof(Deck)*piles);
    dealCards(deck, playersNumber);
}

void GameState::DisplayState() {
    std::cout<<"active player = "<<activePlayer<<"\n";
    std::cout<<"players number = "<<playersNumber<<"\n";
    for(int i = 0; i < playersNumber; i++){
        std::cout<<i+1<<" player hand cards: ";
        playerHand[i].DisplayDeck();
        std::cout<<"\n"<<i+1<<" player deck cards: ";
        playerDeck[i].DisplayDeck();
        std::cout<<"\n";
    }
    for(int i = 1; i < piles + 1; i++){
        std::cout<<i<<" pile cards: "<<"\n";
        pileDeck[i].DisplayDeck();
    }
}

void GameState::dealCards(Deck& deck, int players) {
    Card cards[MAX_PLAYERS][MAX_CARDS_ON_HAND];
    int cardsGiven[MAX_PLAYERS] = {};
    int dealingTo = 0;
    int cardNumber = 0;
    while(deck.cardNumber != 0){
        if(dealingTo >= players){
            dealingTo = 0;
            cardNumber++;
        }
        cards[dealingTo][cardNumber] = deck.RemoveCard(0);
        cardsGiven[dealingTo]++;
        dealingTo++;
    }
    for(int i = 0; i < players; i++){
        playerHand[i] = Deck(cards[i], cardsGiven[i]);
    }

}

GameState::~GameState() {
    free(playerHand);
    free(playerDeck);
}

GameState::GameState(Settings settings, Card playerCards[MAX_PLAYERS][MAX_CARDS_ON_HAND],Card cardsInDeck[MAX_PLAYERS][MAX_CARDS_ON_HAND], Card cardsOnPiles[MAX_PLAYERS][MAX_CARDS_ON_HAND], int* cardsPerPlayer, int* cardsOnHold, int* numberCardsOnPiles) {
    playersNumber = settings.players;
    activePlayer = 1;
    piles = settings.crucibles;
    playerHand = (Deck*)std::malloc(sizeof(Deck)*playersNumber);
    playerDeck = (Deck*)std::malloc(sizeof(Deck)*playersNumber);
    for(int i = 0; i < settings.players; i++){
        playerHand[i] = Deck(playerCards[i], cardsPerPlayer[i]);
        playerDeck[i] = Deck(cardsInDeck[i], cardsOnHold[i]);
    }
    pileDeck = (Deck*)std::malloc(sizeof(Deck)*piles);
    for(int i = 0; i < piles; i++){
        pileDeck[i] = Deck(cardsOnPiles[i], numberCardsOnPiles[i]);
    }
}

void GameState::DisplayCardCount() {
    for(int i = 0; i < playersNumber; i++){
        std::cout<<i+1<<" player has "<<playerHand[i].cardNumber<<" cards on hand"<<"\n";
        std::cout<<i+1<<" player has "<<playerDeck[i].cardNumber<<" cards in front of him"<<"\n";
    }
    for(int i = 0; i < piles; i++){
        std::cout<<"there are "<<pileDeck[i].cardNumber<<" cards on "<<i+1<<" pile\n";
    }
}

void GameState::ValidateGreenCards() {
    int greenValue = -1;
    int greenCount = 0;
    for(int i = 0; i < playersNumber; i++){
        greenCount += playerHand[i].GetColorCount(GREEN);
        greenCount += playerDeck[i].GetColorCount(GREEN);
    }
    for(int i = 0; i < piles; i++){
        greenCount += pileDeck[i].GetColorCount(GREEN);
    }
    if(greenCount == 0)
    {
        std::cout<<"Green cards does not exist";
        return;
    }
    for(int i = 0; i < playersNumber; i++) {
        int tempVal = playerHand[i].GetGreenCardsValue();
        if(tempVal == -2){
            std::cout << "Different green cards values occurred";
            return;
        }
        if (tempVal > 0) {
            if (greenValue != -1 && tempVal != greenValue) {
                std::cout << "Different green cards values occurred";
                return;
            }
            greenValue = tempVal;
        }
        tempVal = playerDeck[i].GetGreenCardsValue();
        if(tempVal == -2){
            std::cout << "Different green cards values occurred";
            return;
        }
        if (tempVal >0) {
            if (greenValue != -1 && tempVal != greenValue) {
               std::cout << "Different green cards values occurred";
               return;
            }
            greenValue = tempVal;
        }
    }
    for(int i = 0; i < piles; i++){
        int tempVal = pileDeck[i].GetGreenCardsValue();
        if(tempVal == -2){
            std::cout << "Different green cards values occurred";
            return;
        }
        if(tempVal>0){
            if(greenValue!=-1&&tempVal!=greenValue){
                std::cout<<"Different green cards values occurred";
                return;
            }
            greenValue = tempVal;
        }
    }
    std::cout<<"Found "<<greenCount<<" green cards, all with "<<greenValue<<" value";
}

void GameState::ValidateCards() {
    int count[COLORS]={};
    for(int i = 0; i < playersNumber;i++){
        for(int j = 0; j < COLORS; j++){
            count[j] += playerHand[i].GetColorCount(j);
            count[j] += playerDeck[i].GetColorCount(j);
        }
    }
    for(int i = 0; i < piles; i++){
        for(int j = 0; j<COLORS;j++){
            count[j] += pileDeck[i].GetColorCount(j);
        }
    }

    for(int i = 1; i < COLORS; i++){
        for(int j = 1; j < COLORS; j++){
            if(i==j)continue;
            if(count[i]!=0&&count[j]!=0&&count[i]!=count[j]){
                std::cout<<"At least two colors with a different number of cards were found:\n";
                for(int k = 1; k < COLORS;k++){
                    if(count[k]!=0){
                        std::cout<<colors[k]<<" cards are "<<count[k]<<"\n";
                    }
                }
                return;
            }
        }
    }
    int i = 1;
    while(count[i]==0)i++;
    std::cout<<"The number cards of all colors is equal: "<<count[i];
}
