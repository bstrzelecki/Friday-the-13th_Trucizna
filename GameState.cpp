#include <cstdlib>
#include <iostream>
#include "GameState.h"

GameState::GameState(Settings settings, Deck& deck) {
    activePlayer = 1;
    playersNumber = settings.players;
    piles = settings.crucibles;
    playerHand = (Deck*)std::malloc(sizeof(Deck)*playersNumber);
    playerDeck = (Deck*)std::malloc(sizeof(Deck)*playersNumber);
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

GameState::GameState(int players, Card playerCards[MAX_PLAYERS][MAX_CARDS_ON_HAND],Card cardsInDeck[MAX_PLAYERS][MAX_CARDS_ON_HAND], int* cardsPerPlayer, int* cardsOnHold) {
    playersNumber = players;
    activePlayer = 1;
    piles = 0;
    playerHand = (Deck*)std::malloc(sizeof(Deck)*playersNumber);
    playerDeck = (Deck*)std::malloc(sizeof(Deck)*playersNumber);
    for(int i = 0; i < players; i++){
        playerHand[i] = Deck(playerCards[i], cardsPerPlayer[i]);
        playerDeck[i] = Deck(cardsInDeck[i], cardsOnHold[i]);
    }
}

void GameState::DisplayCardCount() {
    for(int i = 0; i < playersNumber; i++){
        std::cout<<i+1<<" player has "<<playerHand[i].cardNumber<<" cards on hand"<<"\n";
        std::cout<<i+1<<" player has "<<playerDeck[i].cardNumber<<" cards in front of him"<<"\n";
    }
}
