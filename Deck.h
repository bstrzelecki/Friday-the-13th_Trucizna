#include "statics.h"

class Deck {
public:
    void DisplayDeck() const;
    Deck(Settings settings, int* values);
    Deck(Card* cards, int length);
    Card RemoveCard(int position);
    int cardNumber;
    Card* deck;
private:
    int deckSize;
    void initializeGreenCards(int count, int value) const;
    void initializeCards(Settings settings, int* values) const;
    static void displayCard(Card card);
};