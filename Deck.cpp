#include <iostream>
#include "Deck.h"

void sort(int* array, int length){
    auto swap = [](int* a, int* b){
        int t = *a;
        *a = *b;
        *b = t;
    };

    for(int i = 0; i < length - 1; i++){
        for(int j = 0; j < length - i - j; j++){
            if(array[j]>array[j + 1]){
                swap(&(array[j]),&(array[j+1]));
            }
        }
    }
}

void Deck::DisplayDeck() {
    for(int i = 0; i < deckSize; i++){
        Deck::displayCard(deck[i]);
    }
}

Deck::Deck(Settings settings, int *values) {
    deckSize = settings.totalCards;
    cardNumber = deckSize;
    deck= new Card[deckSize];
    initializeGreenCards(settings.greenCards, settings.greenCardValue);
    sort(values, settings.cardCount);
    initializeCards(settings, values);
}
Deck::Deck(const Deck &deck) {
    deckSize = deck.deckSize;
    cardNumber = deckSize;
    std::memcpy(this->deck, deck.deck, deckSize*sizeof(Deck));
}
Deck::~Deck() {
    delete [] deck;
}

void Deck::initializeGreenCards(int count, int value) {
    for(int i = 0; i < count;i++){
        deck[i] = {value, GREEN};
    }
}

void Deck::initializeCards(Settings settings, int *values) {
    int j = 0;
    int color = 1;
    for(int i = settings.greenCards; i < settings.totalCards; i++,j++){
        if(j >= settings.cardCount){
            color++;
            j = 0;
        }
        deck[i] = {values[j], color};
    }
}

void Deck::displayCard(Card card) {
    std::cout<<card.value << " ";
    std::cout<<colors[card.color]<<" ";
}

Deck &Deck::operator=(const Deck& d) {
    deckSize = d.deckSize;
    std::memcpy(this->deck, d.deck, deckSize*sizeof(Deck));
    return *this;
}
//TEST ME
Deck::Deck(Card *cards, int length) {
    deckSize = length;
    cardNumber = length;
    std::memcpy(deck, cards, deckSize*sizeof(Card));
}
//TEST ME
Card Deck::RemoveCard(int position) {
    Card removed = deck[position];
    for(int i = position; i < cardNumber - 1; i++){
        deck[i] = deck[i+1];
    }
    deck[cardNumber] = {0,0};
    cardNumber--;
    return removed;
}


