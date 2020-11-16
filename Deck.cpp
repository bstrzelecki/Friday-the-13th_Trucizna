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

void Deck::DisplayDeck() const {
    for(int i = 0; i < cardNumber; i++){
        Deck::displayCard(deck[i]);
    }
}

Deck::Deck(Settings settings, int *values) {
    deckSize = settings.totalCards;
    cardNumber = deckSize;
    deck= (Card*)malloc(deckSize*sizeof(Card));
    initializeGreenCards(settings.greenCards, settings.greenCardValue);
    sort(values, settings.cardCount);
    initializeCards(settings, values);
}
void Deck::initializeGreenCards(int count, int value) const {
    for(int i = 0; i < count;i++){
        deck[i] = {value, GREEN};
    }
}

void Deck::initializeCards(Settings settings, int *values) const {
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
Deck::Deck(Card cards[], int length) {
    deckSize = length;
    cardNumber = length;

    deck = (Card*)malloc(deckSize*sizeof(Card));
    for(int i = 0; i < deckSize;i++){
        deck[i].color = cards[i].color;
        deck[i].value = cards[i].value;
    }
}
Card Deck::RemoveCard(int position) {
    Card removed = deck[position];
    for(int i = position; i < cardNumber - 1; i++){
        deck[i] = deck[i+1];
    }
    deck[cardNumber] = {0,0};
    cardNumber--;
    return removed;
}
