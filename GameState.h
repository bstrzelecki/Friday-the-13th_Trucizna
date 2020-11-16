#ifndef POP202_1_GAMESTATE_H
#define POP202_1_GAMESTATE_H

#include "Deck.h"

class GameState {
public:
    GameState(Settings settings, Deck& deck);
    void DisplayState();
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
