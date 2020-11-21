#include <cstdlib>
#include <iostream>
#include "GameState.h"

GameState::GameState(Settings settings, Deck* deck) {
    activePlayer = 0;
    playersNumber = settings.players;
    piles = settings.crucibles;
    explosionThreshold = settings.explosionThreshold;
    MEMTEST(playerHand = (Deck **) std::malloc(sizeof(void*) * playersNumber));
    MEMTEST(playerDeck = (Deck **) std::malloc(sizeof(void*)* playersNumber));
    MEMTEST(pileDeck = (Deck **) std::malloc(sizeof(void*) * piles));
    dealCards(deck, playersNumber);
    for(int i = 0; i < playersNumber; i++){
        playerDeck[i] = new Deck(nullptr,0);
    }
    for(int i = 0; i < piles; i++){
        pileDeck[i] = new Deck(nullptr, 0);
    }
}

void GameState::DisplayState() {
    std::cout << "active player = " << activePlayer + 1 << "\n";
    std::cout << "players number = " << playersNumber << "\n";
    std::cout << "explosion threshold = " << explosionThreshold << "\n";
    for (int i = 0; i < playersNumber; i++) {
        std::cout << i + 1 << " player hand cards: ";
        playerHand[i]->DisplayDeck();
        std::cout << "\n" << i + 1 << " player deck cards: ";
        playerDeck[i]->DisplayDeck();
        std::cout << "\n";
    }
    for (int i = 0; i < piles; i++) {
        std::cout << i + 1 << " pile cards: ";
        pileDeck[i]->DisplayDeck();
        std::cout << "\n";
    }
}

void GameState::dealCards(Deck* deck, int players) {
    Card cards[MAX_PLAYERS][MAX_CARDS_ON_HAND];
    int cardsGiven[MAX_PLAYERS] = {};
    int dealingTo = 0;
    int cardNumber = 0;
    while (deck->cardNumber != 0) {
        if (dealingTo >= players) {
            dealingTo = 0;
            cardNumber++;
        }
        cards[dealingTo][cardNumber] = deck->RemoveCard(0);
        cardsGiven[dealingTo]++;
        dealingTo++;
    }
    for (int i = 0; i < players; i++) {
        playerHand[i] = new Deck(cards[i], cardsGiven[i]);
    }

}

GameState::~GameState() {
    free(playerHand);
    free(playerDeck);
    free(pileDeck);
}

GameState::GameState(Settings settings, Card playerCards[MAX_PLAYERS][MAX_CARDS_ON_HAND],
                     Card cardsInDeck[MAX_PLAYERS][MAX_CARDS_ON_HAND],
                     Card cardsOnPiles[MAX_PLAYERS][MAX_CARDS_ON_HAND], int *cardsPerPlayer, int *cardsOnHold,
                     int *numberCardsOnPiles) {
    playersNumber = settings.players;
    activePlayer = settings.activePlayer - 1;
    explosionThreshold = settings.explosionThreshold;
    piles = settings.crucibles;
    MEMTEST(playerDeck = (Deck **) std::malloc(sizeof(void*) * playersNumber))
    MEMTEST(playerHand = (Deck **) std::malloc(sizeof(void*) * playersNumber))
    for (int i = 0; i < settings.players; i++) {
        playerHand[i] = new Deck(playerCards[i], cardsPerPlayer[i]);
        playerDeck[i] = new Deck(cardsInDeck[i], cardsOnHold[i]);
    }
    pileDeck = (Deck **) std::malloc(sizeof(void*) * piles);
    for (int i = 0; i < piles; i++) {
        pileDeck[i] = new Deck(cardsOnPiles[i], numberCardsOnPiles[i]);
    }
}

void GameState::DisplayCardCount() {
    for (int i = 0; i < playersNumber; i++) {
        std::cout << i + 1 << " player has " << playerHand[i]->cardNumber << " cards on hand" << "\n";
        std::cout << i + 1 << " player has " << playerDeck[i]->cardNumber << " cards in front of him" << "\n";
    }
    for (int i = 0; i < piles; i++) {
        std::cout << "there are " << pileDeck[i]->cardNumber << " cards on " << i + 1 << " pile\n";
    }
}

int GameState::checkGreenCardCount() {
    int greenCount = 0;
    for (int i = 0; i < playersNumber; i++) {
        greenCount += playerHand[i]->GetColorCount(GREEN);
        greenCount += playerDeck[i]->GetColorCount(GREEN);
    }
    for (int i = 0; i < piles; i++) {
        greenCount += pileDeck[i]->GetColorCount(GREEN);
    }
    if (greenCount == 0) {
        std::cout << "Green cards does not exist\n";
        return 0;
    }
    return greenCount;
}

VALIDATION_RESULT GameState::checkGreenCardValue(Deck* deck, int* greenValue) {
    int tempVal = deck->GetGreenCardsValue();
    if (tempVal == -2) {
        std::cout << "Different green cards values occurred\n";
        return VALIDATION_ERROR;
    }
    if (tempVal > 0) {
        if (*greenValue != -1 && tempVal != *greenValue) {
            std::cout << "Different green cards values occurred\n";
            return VALIDATION_ERROR;
        }
        *greenValue = tempVal;
    }
    return VALIDATION_SUCCESS;
}

VALIDATION_RESULT GameState::ValidateGreenCards() {
    int greenValue = -1;
    int greenCount = 0;
    greenCount = checkGreenCardCount();
    if(greenCount == 0)
        return VALIDATION_ERROR;
    for (int i = 0; i < playersNumber; i++) {
        VALIDATION_RESULT result = checkGreenCardValue(playerHand[i], &greenValue);
        if(result == VALIDATION_ERROR)
            return VALIDATION_ERROR;
        result = checkGreenCardValue(playerDeck[i], &greenValue);
        if(result == VALIDATION_ERROR)
            return VALIDATION_ERROR;
    }
    for (int i = 0; i < piles; i++) {
        VALIDATION_RESULT result = checkGreenCardValue(pileDeck[i], &greenValue);
        if(result == VALIDATION_ERROR)
            return VALIDATION_ERROR;
    }
    std::cout << "Found " << greenCount << " green cards, all with " << greenValue << " value\n";
    return VALIDATION_SUCCESS;

}
VALIDATION_RESULT GameState::ValidateCards() {
    int count[COLORS] = {};
    for (int i = 0; i < playersNumber; i++) {
        for (int j = 0; j < COLORS; j++) {
            count[j] += playerHand[i]->GetColorCount(j);
            count[j] += playerDeck[i]->GetColorCount(j);
        }
    }
    for (int i = 0; i < piles; i++) {
        for (int j = 0; j < COLORS; j++) {
            count[j] += pileDeck[i]->GetColorCount(j);
        }
    }

    for (int i = 1; i < COLORS; i++) {
        for (int j = 1; j < COLORS; j++) {
            if (i == j)continue;
            if (count[i] != 0 && count[j] != 0 && count[i] != count[j]) {
                std::cout << "At least two colors with a different number of cards were found:\n";
                for (int k = 1; k < COLORS; k++) {
                    if (count[k] != 0) {
                        std::cout << colors[k] << " cards are " << count[k] << "\n";
                    }
                }
                return VALIDATION_ERROR;
            }
        }
    }
    int i = 1;
    while (count[i] == 0)i++;
    std::cout << "The number cards of all colors is equal: " << count[i]<<"\n";
    return VALIDATION_SUCCESS;
}

void displayColorValues(int valueCount[COLORS][MAX_VALUE]) {
    for (int i = 1; i < COLORS; i++) {
        std::cout << colors[i] << " cards values: ";
        for (int j = 0; j < MAX_VALUE; j++) {
            for (int k = 0; k < valueCount[i][j]; k++) {
                std::cout << j << " ";
            }
        }
        std::cout << "\n";
    }
}

VALIDATION_RESULT GameState::ValidateCardValues() {
    int valueCount[COLORS][MAX_VALUE] = {};
    for (int i = 0; i < playersNumber; i++) {
        for (int j = 0; j < playerHand[i]->cardNumber; j++) {
            Card card = playerHand[i]->deck[j];
            valueCount[card.color][card.value]++;
        }
        for (int j = 0; j < playerDeck[i]->cardNumber; j++) {
            Card card = playerDeck[i]->deck[j];
            valueCount[card.color][card.value]++;
        }
    }
    for (int i = 0; i < piles; i++) {
        for (int j = 0; j < pileDeck[i]->cardNumber; j++) {
            Card card = pileDeck[i]->deck[j];
            valueCount[card.color][card.value]++;
        }
    }
    for (int i = 1; i < piles; i++) {
        for (int j = 1; j < piles; j++) {
            if (i == j)continue;
            for (int k = 0; k < MAX_VALUE; k++) {
                if (valueCount[i][k] != valueCount[j][k]) {
                    std::cout << "The values of cards of all colors are not identical:\n";
                    displayColorValues(valueCount);
                    return VALIDATION_ERROR;
                }
            }
        }
    }
    std::cout << "The values of cards of all colors are identical:\n";
    for (int j = 0; j < MAX_VALUE; j++) {
        for (int k = 0; k < valueCount[BLUE][j]; k++) {
            std::cout << j << " ";
        }
    }
    std::cout << "\n";
    return VALIDATION_SUCCESS;
}

VALIDATION_RESULT GameState::ValidatePiles() {
    int valid = VALIDATION_SUCCESS;
    for (int i = 0; i < piles; i++) {
        int col = 0;
        for (int j = 1; j < COLORS; j++) {
            int count = pileDeck[i]->GetColorCount(j);
            if (count != 0) {
                if (col == 0) {
                    col = j;
                } else {
                    std::cout << "Two different colors were found on the " << i + 1 << " pile\n";
                    valid = VALIDATION_ERROR;
                    break;
                }
            }
        }
    }
    for (int i = 0; i < piles; i++) {
        if (pileDeck[i]->GetCardsValue() > explosionThreshold) {
            std::cout << "Pile number " << i + 1 << " should explode earlier\n";
            valid = VALIDATION_ERROR;
        }
    }
    return valid;
}

VALIDATION_RESULT GameState::ValidateHands() {
    for (int i = 0; i < playersNumber - 1; i++) {
        if (playerHand[i]->cardNumber == playerHand[i + 1]->cardNumber) {
            continue;
        }
        if (playerHand[i]->cardNumber == (playerHand[i + 1]->cardNumber + 1)) {
            continue;
        }
        if ((i + 1) == (activePlayer) && playerHand[i]->cardNumber == (playerHand[i + 1]->cardNumber - 1)) {
            continue;
        }
        std::cout << "The number of players cards on hand is wrong\n";
        return VALIDATION_ERROR;
    }
    return VALIDATION_SUCCESS;
}

void GameState::Play(int cardPosition, int pileIfGreen) {
    int currentPlayer = activePlayer;
    Card card = playerHand[activePlayer]->RemoveCard(cardPosition);
    activePlayer++;
    if (activePlayer > playersNumber - 1)
        activePlayer = 0;
    if (card.color == GREEN) {
        pileDeck[pileIfGreen]->AddCard(card);
    } else {
        for (int i = 0; i < piles; i++) {
            if (pileDeck[i]->GetColorCount(card.color) > 0) {
                pileDeck[i]->AddCard(card);
                handleExplosion(currentPlayer, i);
                return;
            }
        }
        for (int i = 0; i < piles; i++) {
            int isEmpty = 1;
            for (int j = 1; j < COLORS; j++) {
                if (pileDeck[i]->GetColorCount(j) != 0) {
                    isEmpty = 0;
                    break;
                }
            }
            if (isEmpty == 1) {
                pileDeck[i]->AddCard(card);
                handleExplosion(currentPlayer, i);
                return;
            }
        }

    }
}

void GameState::handleExplosion(int player, int pile) {
    if (pileDeck[pile]->GetCardsValue() > explosionThreshold) {
        while (pileDeck[pile]->cardNumber > 0) {
            Card card = pileDeck[pile]->RemoveCard(0);
            playerDeck[player]->AddCard(card);
        }
    }
}

void GameState::DisplayScore() {
    int max[COLORS];
    for (int i = 1; i < COLORS; i++) {
        int localMax = -1;
        int maxValue = 0;
        int unique = 1;
        for (int j = 0; j < playersNumber; j++) {
            int count = playerDeck[j]->GetColorCount(i);
            if (count > maxValue) {
                maxValue = count;
                unique = 1;
                localMax = j;
            } else if (count == maxValue) {
                unique = 0;
            }
        }
        if (unique == 0) {
            localMax = -1;
        }
        max[i] = localMax;
    }
    int immunity[MAX_PLAYERS][COLORS] = {};
    for (int i = 1; i < COLORS; i++) {
        if (max[i] != -1) {
            immunity[max[i]][i] = 1;
            std::cout << "Na kolor " << colors[i] << " odporny jest gracz " << max[i] + 1 << "\n";
        }
    }
    for (int i = 0; i < playersNumber; i++) {
        std::cout << "Wynik gracza " << i + 1 << " = " << playerDeck[i]->GetFinalValue(immunity[i]) << "\n";
    }
}

void GameState::DisplayValidationResult() {
    if(ValidateGreenCards() == VALIDATION_SUCCESS &&
       ValidateCards() == VALIDATION_SUCCESS &&
       ValidateCardValues() == VALIDATION_SUCCESS &&
       ValidateHands() == VALIDATION_SUCCESS &&
       ValidatePiles() == VALIDATION_SUCCESS)
    {
        std::cout<<"The current state of the game is ok\n";
    }
}

int GameState::IsGameOver() {
    if(playerHand[activePlayer]->cardNumber == 0){
        return 1;
    }else{
        return 0;
    }

}

