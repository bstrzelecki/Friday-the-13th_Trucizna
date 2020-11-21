#ifndef POP202_1_GAMESTATE_H
#define POP202_1_GAMESTATE_H

#include "Deck.h"

class GameState {
public:
    GameState(Settings settings, Deck* deck);

    GameState(Settings settings, Card playerCards[MAX_PLAYERS][MAX_CARDS_ON_HAND],
              Card cardsInDeck[MAX_PLAYERS][MAX_CARDS_ON_HAND], Card cardsOnPiles[MAX_PLAYERS][MAX_CARDS_ON_HAND],
              int *cardsPerPlayer, int *cardsOnHold, int *numberCardsOnPiles);

    void Play(int card, int pileIfGreen = 0);

    int IsGameOver();

    void DisplayState();

    void DisplayCardCount();

    void DisplayScore();

    void DisplayValidationResult();

    VALIDATION_RESULT ValidateGreenCards();

    VALIDATION_RESULT ValidateCards();

    VALIDATION_RESULT ValidateCardValues();

    VALIDATION_RESULT ValidateHands();

    VALIDATION_RESULT ValidatePiles();

    ~GameState();

private:
    void handleExplosion(int player, int pile);

    void dealCards(Deck* deck, int players);

    int checkGreenCardCount();

    VALIDATION_RESULT checkGreenCardValue(Deck* deck, int* greenValue);

    int activePlayer;
    int piles;
    int playersNumber;
    int explosionThreshold;
    Deck** playerHand;
    Deck** playerDeck;
    Deck** pileDeck;
};


#endif
