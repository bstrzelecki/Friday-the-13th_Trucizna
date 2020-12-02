#include "statics.h"

class Deck {
public:
    void DisplayDeck() const;

    Deck(Settings settings, int *values);

    Deck(Card *cards, int length);

    ~Deck();

    // Input: position of card that will be removed from deck
    // Output: card contained at given index
    Card RemoveCard(int position);

    Card PeekCard(int position);

    void AddCard(Card card);

    // Input number (0-6) representing color (Card.color)
    // Output: amount of cards that Card.color matches colorId
    int GetColorCount(int colorId) const;

    // Output: returns sum of Card.value of cards where Card.color == GREEN (0)
    int GetGreenCardsValue() const;

    // Output: sum oof Card.value of all cards
    int GetCardsValue() const;

    // Output: amount of cards that's currently stored in deck[]
    int GetCardsCount() const;

    // Output: amount of cards that's currently stored in deck[] without ones with Card.color == GREEN (0)
    int GetNonGreenCardCount();

    // Output: first non GREEN (0) color id.
    // When deck is empty returns -1.
    // When in deck are only GREEN (0) cards returns GREEN (0)
    COLOR GetContainedColor();

    // Input: table that link colors with immunity if immunity[COLOR] == 1 then cards with this color are not added to the score
    // Output: number of points from this deck according to immunity
    int GetFinalValue(const int immunity[]);

private:
    // amount of cards that's currently stored in deck[]
    int cardNumber;
    // size of deck[]
    int deckSize;
    Card *deck;

    void initializeGreenCards(int count, int value) const;

    void initializeCards(Settings settings, int *values) const;

    static void displayCard(Card card);
};