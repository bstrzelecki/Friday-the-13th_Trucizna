#ifndef POP202_1_GAMESTATE_H
#define POP202_1_GAMESTATE_H

#include "Deck.h"

class GameState {
public:
    GameState(Settings settings, Deck& deck);
    GameState(int players, Card playerCards[MAX_PLAYERS][MAX_CARDS_ON_HAND],Card cardsInDeck[MAX_PLAYERS][MAX_CARDS_ON_HAND], int* cardsPerPlayer, int* cardsOnHold);
    void DisplayState();
    void DisplayCardCount();
    ~GameState();
private:
    void dealCards(Deck& deck, int players);
    int activePlayer;
    int piles;
    int playersNumber;
    Deck* playerHand;
    Deck* playerDeck;
};


#endif
