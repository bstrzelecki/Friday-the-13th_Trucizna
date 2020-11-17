#ifndef POP202_1_GAMESTATE_H
#define POP202_1_GAMESTATE_H

#include "Deck.h"

class GameState {
public:
    GameState(Settings settings, Deck& deck);
    GameState(Settings settings, Card playerCards[MAX_PLAYERS][MAX_CARDS_ON_HAND],Card cardsInDeck[MAX_PLAYERS][MAX_CARDS_ON_HAND], Card cardsOnPiles[MAX_PLAYERS][MAX_CARDS_ON_HAND], int* cardsPerPlayer, int* cardsOnHold, int* numberCardsOnPiles);
    void DisplayState();
    void DisplayCardCount();
    void ValidateGreenCards();
    void ValidateCards();
    ~GameState();
private:
    void dealCards(Deck& deck, int players);
    int activePlayer;
    int piles;
    int playersNumber;
    Deck* playerHand;
    Deck* playerDeck;
    Deck* pileDeck;
};


#endif
