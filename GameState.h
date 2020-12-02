#ifndef POP202_1_GAMESTATE_H
#define POP202_1_GAMESTATE_H

#include "Deck.h"

class GameState {
public:
    GameState(Settings settings, Deck *deck);

    GameState(Settings settings, Card playerCards[MAX_PLAYERS][MAX_CARDS_ON_HAND],
              Card cardsInDeck[MAX_PLAYERS][MAX_CARDS_ON_HAND], Card cardsOnPiles[MAX_PLAYERS][MAX_CARDS_ON_HAND],
              int *cardsPerPlayer, int *cardsOnHold, int *numberCardsOnPiles);

    void Play(int card, int defaultPile = 0);

    // Output: 1 if number of cards in active player's hand is equal to 0 otherwise 0
    int IsGameOver();

    void DisplayState();

    void DisplayCardCount();

    void DisplayScore();

    void DisplayValidationResult();

    Deck* GetActiveHand();

    Deck* GetActivePlayerDeck();

    // Output: pointer to crucible with given index
    Deck* GetPile(int n);

    // Input: color id
    // Output: deck of cards where cards have either green of {color} color.
    Deck* GetPileWithColor(COLOR color);

    // Input: color id
    // Output: index of deck of cards where cards have either green of {color} color.
    int GetPileIdWithColor(COLOR color);

    // Output: number of crucibles
    int GetPileCount() const;

    // Output: number of currently acting player
    int GetActivePlayer() const;

    int GetExplosionThreshold();

    int GetPlayerScore(int player);

    VALIDATION_RESULT ValidateGreenCards();

    VALIDATION_RESULT ValidateCards();

    VALIDATION_RESULT ValidateCardValues();

    VALIDATION_RESULT ValidateHands();

    VALIDATION_RESULT ValidatePiles();

    ~GameState();

private:
    int* getPlayerImmunity(int player);

    void handleExplosion(int player, int pile);

    void dealCards(Deck *deck, int players);

    int checkGreenCardCount();

    static VALIDATION_RESULT checkGreenCardValue(Deck *deck, int *greenValue);

    int activePlayer;
    int piles;
    int playersNumber;
    int explosionThreshold;
    Deck **playerHand;
    Deck **playerDeck;
    Deck **pileDeck;
};


#endif
