#include <cstdlib>
#include <cstdio>
#include "GameState.h"

GameState::GameState(Settings settings, Deck *deck) {
    activePlayer = 0;
    playersNumber = settings.players;
    piles = settings.crucibles;
    explosionThreshold = settings.explosionThreshold;
    MEMTEST(playerHand = (Deck **) malloc(sizeof(void *) * playersNumber));
    MEMTEST(playerDeck = (Deck **) malloc(sizeof(void *) * playersNumber));
    MEMTEST(pileDeck = (Deck **) malloc(sizeof(void *) * piles));
    dealCards(deck, playersNumber);
    for (int i = 0; i < playersNumber; i++) {
        playerDeck[i] = new Deck(nullptr, 0);
    }
    for (int i = 0; i < piles; i++) {
        pileDeck[i] = new Deck(nullptr, 0);
    }
}

void GameState::DisplayState() {
    printf("active player = %i\n", activePlayer + 1);
    printf("players number = %i\n", playersNumber);
    printf("explosion threshold =  %i\n", explosionThreshold);
    for (int i = 0; i < playersNumber; i++) {
        printf("%i player hand cards: ", i + 1);
        playerHand[i]->DisplayDeck();
        printf("\n%i player deck cards: ", i + 1);
        playerDeck[i]->DisplayDeck();
        printf("\n");
    }
    for (int i = 0; i < piles; i++) {
        printf("%i pile cards: ", i + 1);
        pileDeck[i]->DisplayDeck();
        printf("\n");
    }
}

void GameState::dealCards(Deck *deck, int players) {
    Card cards[MAX_PLAYERS][MAX_CARDS_ON_HAND];
    int cardsGiven[MAX_PLAYERS] = {};
    int dealingTo = 0;
    int cardNumber = 0;
    while (deck->GetCardsCount() != 0) {
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
    for(int i = 0; i < playersNumber; i++){
        delete playerHand[i];
        delete playerDeck[i];
    }
    for(int i = 0; i < piles; i++){
        delete pileDeck[i];
    }
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
    MEMTEST(playerDeck = (Deck **) std::malloc(sizeof(void *) * playersNumber))
    MEMTEST(playerHand = (Deck **) std::malloc(sizeof(void *) * playersNumber))
    for (int i = 0; i < settings.players; i++) {
        playerHand[i] = new Deck(playerCards[i], cardsPerPlayer[i]);
        playerDeck[i] = new Deck(cardsInDeck[i], cardsOnHold[i]);
    }
    pileDeck = (Deck **) std::malloc(sizeof(void *) * piles);
    for (int i = 0; i < piles; i++) {
        pileDeck[i] = new Deck(cardsOnPiles[i], numberCardsOnPiles[i]);
    }
}

void GameState::DisplayCardCount() {
    for (int i = 0; i < playersNumber; i++) {
        printf("%i player has %i cards on hand\n", i + 1, playerHand[i]->GetCardsCount());
        printf("%i player has %i cards in front of him\n", i + 1, playerDeck[i]->GetCardsCount());
    }
    for (int i = 0; i < piles; i++) {
        printf("there are %i cards on %i pile\n", pileDeck[i]->GetCardsCount(), i + 1);
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
        printf("Green cards does not exist\n");
        return 0;
    }
    return greenCount;
}

VALIDATION_RESULT GameState::checkGreenCardValue(Deck *deck, int *greenValue) {
    int tempVal = deck->GetGreenCardsValue();
    if (tempVal == -2) {
        printf("Different green cards values occurred\n");
        return VALIDATION_ERROR;
    }
    if (tempVal > 0) {
        if (*greenValue != -1 && tempVal != *greenValue) {
            printf("Different green cards values occurred\n");
            return VALIDATION_ERROR;
        }
        *greenValue = tempVal;
    }
    return VALIDATION_SUCCESS;
}

VALIDATION_RESULT GameState::ValidateGreenCards(int verbose) {
    int greenValue = -1;
    int greenCount = checkGreenCardCount();
    if (greenCount == 0)
        return VALIDATION_ERROR;
    for (int i = 0; i < playersNumber; i++) {
        VALIDATION_RESULT result = checkGreenCardValue(playerHand[i], &greenValue);
        if (result == VALIDATION_ERROR)
            return VALIDATION_ERROR;
        result = checkGreenCardValue(playerDeck[i], &greenValue);
        if (result == VALIDATION_ERROR)
            return VALIDATION_ERROR;
    }
    for (int i = 0; i < piles; i++) {
        VALIDATION_RESULT result = checkGreenCardValue(pileDeck[i], &greenValue);
        if (result == VALIDATION_ERROR)
            return VALIDATION_ERROR;
    }
    if(verbose != 0)printf("Found %i green cards, all with %i value\n", greenCount, greenValue);
    return VALIDATION_SUCCESS;

}

VALIDATION_RESULT GameState::ValidateCards(int verbose) {
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
                if(verbose != 0)printf("At least two colors with a different number of cards were found:\n");
                for (int k = 1; k < COLORS; k++) {
                    if (count[k] != 0) {
                        if(verbose != 0)printf("%s cards are %i\n", colors[k], count[k]);
                    }
                }
                return VALIDATION_ERROR;
            }
        }
    }
    int i = 1;
    while (count[i] == 0)i++;
    if(verbose != 0)printf("The number cards of all colors is equal: %i\n", count[i]);
    return VALIDATION_SUCCESS;
}

void displayColorValues(int valueCount[COLORS][MAX_VALUE]) {
    for (int i = 1; i < COLORS; i++) {
        printf("%s card values: ", colors[i]);
        for (int j = 0; j < MAX_VALUE; j++) {
            for (int k = 0; k < valueCount[i][j]; k++) {
                printf("%i ", j);
            }
        }
        printf("\n");
    }
}

VALIDATION_RESULT GameState::ValidateCardValues(int verbose) {
    int valueCount[COLORS][MAX_VALUE] = {};
    for (int i = 0; i < playersNumber; i++) {
        for (int j = 0; j < playerHand[i]->GetCardsCount(); j++) {
            Card card = playerHand[i]->PeekCard(j);
            valueCount[card.color][card.value]++;
        }
        for (int j = 0; j < playerDeck[i]->GetCardsCount(); j++) {
            Card card = playerDeck[i]->PeekCard(j);
            valueCount[card.color][card.value]++;
        }
    }
    for (int i = 0; i < piles; i++) {
        for (int j = 0; j < pileDeck[i]->GetCardsCount(); j++) {
            Card card = pileDeck[i]->PeekCard(j);
            valueCount[card.color][card.value]++;
        }
    }
    for (int i = 1; i < piles; i++) {
        for (int j = 1; j < piles; j++) {
            if (i == j)continue;
            for (int k = 0; k < MAX_VALUE; k++) {
                if (valueCount[i][k] != valueCount[j][k]) {
                    if(verbose != 0)printf("The values of cards of all colors are not identical:\n");
                    displayColorValues(valueCount);
                    return VALIDATION_ERROR;
                }
            }
        }
    }
    if(verbose != 0)printf("The values of cards of all colors are identical:\n");
    for (int j = 0; j < MAX_VALUE; j++) {
        for (int k = 0; k < valueCount[BLUE][j]; k++) {
            if(verbose != 0)printf("%i ", j);
        }
    }
    if(verbose != 0)printf("\n");
    return VALIDATION_SUCCESS;
}

VALIDATION_RESULT GameState::ValidatePiles(int verbose) {
    int valid = VALIDATION_SUCCESS;
    for (int i = 0; i < piles; i++) {
        int col = 0;
        for (int j = 1; j < COLORS; j++) {
            int count = pileDeck[i]->GetColorCount(j);
            if (count != 0) {
                if (col == 0) {
                    col = j;
                } else {
                    if(verbose != 0)printf("Two different colors were found on the %i pile\n", i + 1);
                    valid = VALIDATION_ERROR;
                    break;
                }
            }
        }
    }
    for (int i = 0; i < piles; i++) {
        if (pileDeck[i]->GetCardsValue() > explosionThreshold) {
            if(verbose != 0)printf("Pile number %i should explode earlier\n", i + 1);
            valid = VALIDATION_ERROR;
        }
    }
    return valid;
}

VALIDATION_RESULT GameState::ValidateHands(int verbose) {
    for (int i = 0; i < playersNumber - 1; i++) {
        if (playerHand[i]->GetCardsCount() == playerHand[i + 1]->GetCardsCount()) {
            continue;
        }
        if (playerHand[i]->GetCardsCount() == (playerHand[i + 1]->GetCardsCount() + 1)) {
            continue;
        }
        if ((i + 1) == (activePlayer) && playerHand[i]->GetCardsCount() == (playerHand[i + 1]->GetCardsCount() - 1)) {
            continue;
        }
        if(verbose != 0)printf("The number of players cards on hand is wrong\n");
        return VALIDATION_ERROR;
    }
    return VALIDATION_SUCCESS;
}

void GameState::Play(int cardPosition, int defaultPile) {
    int currentPlayer = activePlayer;
    if(cardPosition == -1 || defaultPile == -1){
        cardPosition = 0;
        defaultPile = 0;
    }
    Card card = playerHand[activePlayer]->RemoveCard(cardPosition);
    activePlayer++;
    if (activePlayer > playersNumber - 1)
        activePlayer = 0;
    if (card.color == GREEN) {
        pileDeck[defaultPile]->AddCard(card);
        handleExplosion(currentPlayer, defaultPile);
    } else {
        for (int i = 0; i < piles; i++) {
            if (pileDeck[i]->GetColorCount(card.color) > 0) {
                pileDeck[i]->AddCard(card);
                handleExplosion(currentPlayer, i);
                return;
            }
        }
        {
            int isEmpty = 1;
            for (int i = 1; i < COLORS; i++) {
                if (pileDeck[defaultPile]->GetColorCount(i) != 0) {
                    isEmpty = 0;
                    break;
                }
            }
            if (isEmpty == 1) {
                pileDeck[defaultPile]->AddCard(card);
                handleExplosion(currentPlayer, defaultPile);
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
        while (pileDeck[pile]->GetCardsCount() > 0) {
            Card card = pileDeck[pile]->RemoveCard(0);
            playerDeck[player]->AddCard(card);
        }
    }
}
int* GameState::getPlayerImmunity(int player) {
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
    int* immunity = new int[COLORS];
    for (int i = 1; i < COLORS; i++) {
        if (max[i] == player) {
            immunity[i] = 1;
        }else{
            immunity[i] = 0;
        }
    }
    return immunity;
}

void GameState::DisplayScore() {
    for (int i = 1; i < COLORS; i++) {
        for(int j = 0; j < playersNumber; j++){
            int* immunity = getPlayerImmunity(j);
            if(immunity[i] == 1){
                printf("Na kolor %s odporny jest gracz %i\n", colors[i], j + 1);
            }
            delete [] immunity;
        }

    }
    for (int i = 0; i < playersNumber; i++) {
        printf("Wynik gracza %i = %i\n", i + 1, GetPlayerScore(i));
    }
}

int GameState::GetPlayerScore(int player) {
    int* immunity = getPlayerImmunity(player);
    int score = playerDeck[player]->GetFinalValue(immunity);
    delete [] immunity;
    return score;
}


void GameState::DisplayValidationResult() {
    if (ValidateGreenCards() == VALIDATION_SUCCESS &&
        ValidateCards() == VALIDATION_SUCCESS &&
        ValidateCardValues() == VALIDATION_SUCCESS &&
        ValidateHands() == VALIDATION_SUCCESS &&
        ValidatePiles() == VALIDATION_SUCCESS) {
        printf("The current state of the game is ok\n");
    }
}

int GameState::IsGameOver() {
    if (playerHand[activePlayer]->GetCardsCount() == 0) {
        return 1;
    } else {
        return 0;
    }

}

Deck *GameState::GetActiveHand() {
    return playerHand[activePlayer];
}

Deck *GameState::GetPile(int n) {
    if(n < piles){
        return pileDeck[n];
    }else{
        return nullptr;
    }
}

int GameState::GetPileCount() const {
    return piles;
}

Deck *GameState::GetPileWithColor(COLOR color) {
    for(int i = 0; i < piles; i++){
        if(pileDeck[i]->GetColorCount(color) > 0)
            return pileDeck[i];
    }
    return nullptr;
}

int GameState::GetPileIdWithColor(COLOR color) {
    for(int i = 0; i < piles; i++){
        if(pileDeck[i]->GetColorCount(color) > 0)
            return i;
    }
    return -1;
}

int GameState::GetExplosionThreshold() const{
    return explosionThreshold;
}

Deck *GameState::GetActivePlayerDeck() {
    return playerDeck[activePlayer];
}

int GameState::GetActivePlayer() const {
    return activePlayer;
}

void GameState::AdvanceActivePlayer(int player) {
    activePlayer += player;
    if(activePlayer > playersNumber)
        activePlayer = playersNumber - activePlayer;
}



