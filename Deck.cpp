#include <cstdio>
#include <cstdlib>
#include "Deck.h"
#include <time.h>

void sort(int *array, int length) {
    auto swap =[](int* a, int* b){
        int t = *a;
        *a = *b;
        *b = t;
    };
    for (int i = 0; i < length - 1; i++) {
        for (int j = 0; j < length - i - j; j++) {
            if (array[j] > array[j + 1]) {
                swap(&(array[j]), &(array[j + 1]));
            }
        }
    }
}
void shuffle(Card* array, int length){
    auto swap =[](Card* a, Card* b){
        Card t = *a;
        *a = *b;
        *b = t;
    };
    srand(time(nullptr));
    for(int i = 0; i < length; i++){
        int pos = rand()%length;
        swap(&array[i], &array[pos]);
    }
}

void Deck::DisplayDeck() const {
    for (int i = 0; i < cardNumber; i++) {
        Deck::displayCard(deck[i]);
    }
}

Deck::Deck(Settings settings, int *values) {
    deckSize = settings.totalCards;
    cardNumber = deckSize;
    MEMTEST(deck = (Card *) malloc(deckSize * sizeof(Card)))
    initializeGreenCards(settings.greenCards, settings.greenCardValue);
    sort(values, settings.cardCount);
    initializeCards(settings, values);
    shuffle(deck, deckSize);
}

void Deck::initializeGreenCards(int count, int value) const {
    for (int i = 0; i < count; i++) {
        deck[i] = {value, GREEN};
    }
}

void Deck::initializeCards(Settings settings, int *values) const {
    int j = 0;
    int color = 1;
    for (int i = settings.greenCards; i < settings.totalCards; i++, j++) {
        if (j >= settings.cardCount) {
            color++;
            j = 0;
        }
        deck[i] = {values[j], color};
    }
}

void Deck::displayCard(Card card) {
    if(card.value<0||card.color<0){
        printf("ISSUE");
        return;
    }
    printf("%i %s ", card.value, colors[card.color]);
}

Deck::Deck(Card cards[], int length) {
    deckSize = length;
    cardNumber = length;
    if (length == 0)return;
    MEMTEST(deck = (Card *) malloc(deckSize * sizeof(Card)))
    for (int i = 0; i < deckSize; i++) {
        deck[i].color = cards[i].color;
        deck[i].value = cards[i].value;
    }
}

Card Deck::RemoveCard(int position) {
    Card removed = deck[position];
    for (int i = position; i < cardNumber - 1; i++) {
        deck[i] = deck[i + 1];
    }
    cardNumber--;
    return removed;
}

void Deck::AddCard(Card card) {
    if (cardNumber < deckSize) {
        deck[cardNumber] = card;
        cardNumber++;
    } else {
        Card *oldDeck = deck;
        cardNumber++;
        MEMTEST(deck = (Card *) malloc(cardNumber * sizeof(Card)))
        for (int i = 0; i < cardNumber - 1; i++) {
            deck[i].color = oldDeck[i].color;
            deck[i].value = oldDeck[i].value;
        }
        deck[cardNumber - 1].color = card.color;
        deck[cardNumber - 1].value = card.value;
        if (deckSize != 0) {
            free(oldDeck);
        }
        deckSize = cardNumber;
    }
}

int Deck::GetColorCount(int colorId) const {
    int count = 0;
    for (int i = 0; i < cardNumber; i++) {
        if (deck[i].color == colorId)
            count++;
    }
    return count;
}

int Deck::GetGreenCardsValue() const {
    int value = -1;
    for (int i = 0; i < cardNumber; i++) {
        if (deck[i].color == GREEN) {
            if (value == -1)
                value = deck[i].value;
            if (value != -1 && value != deck[i].value) {
                value = -2;
                break;
            }
        }
    }
    return value;
}

int Deck::GetCardsValue() const {
    int sum = 0;
    for (int i = 0; i < cardNumber; i++) {
        sum += deck[i].value;
    }
    return sum;
}

int Deck::GetFinalValue(const int *immunity) {
    int sum = 0;
    for (int i = 0; i < cardNumber; i++) {
        if (deck[i].color == GREEN) {
            sum += 2;
        } else if (deck[i].color > 0 && immunity[deck[i].color] != 1) {
            sum += 1;
        }

    }
    return sum;
}

Deck::~Deck() {
    if (deckSize != 0) {
        free(deck);
    }
}

Card Deck::PeekCard(int position) {
    return deck[position];
}

int Deck::GetCardsCount() const {
    return cardNumber;
}

int Deck::GetNonGreenCardCount() {
    int count = 0;
    for(int i = 0; i < cardNumber;i++){
        if(deck[i].color != GREEN){
            count++;
        }
    }
    return count;
}

COLOR Deck::GetContainedColor() {
    int containsGreen = -1;
    for(int i = 0; i < cardNumber; i++){
        if(deck[i].color != GREEN){
            return deck[i].color;
        }else{
            containsGreen = 0;
        }
    }
    return containsGreen;
}
