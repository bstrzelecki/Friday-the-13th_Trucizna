#include "statics.h"

class Deck {
public:
    void DisplayDeck();
    Deck(Settings settings, int* values);
    Deck(Card* cards, int length);
    Deck(const Deck& deck);
    ~Deck();
    Deck& operator=(const Deck& d);
    Card RemoveCard(int position);
private:
    Card* deck;
    int deckSize;
    int cardNumber;
    void initializeGreenCards(int count, int value);
    void initializeCards(Settings settings, int* values);
    static void displayCard(Card card);
};