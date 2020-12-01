#include "statics.h"

class Deck {
public:
    void DisplayDeck() const;

    Deck(Settings settings, int *values);

    Deck(Card *cards, int length);

    ~Deck();

    Card RemoveCard(int position);

    Card PeekCard(int position);

    void AddCard(Card card);

    int GetColorCount(int colorId) const;

    int GetGreenCardsValue() const;

    int GetCardsValue() const;

    int GetCardsCount() const;

    int GetNonGreenCardCount();

    COLOR GetContainedColor();

    int GetFinalValue(const int immunity[]);

private:
    int cardNumber;
    int deckSize;
    Card *deck;

    void initializeGreenCards(int count, int value) const;

    void initializeCards(Settings settings, int *values) const;

    static void displayCard(Card card);
};