#include <cstdio>
#include "statics.h"
#include "GameState.h"
#include "StateParser.h"

GameState *getState(GameState *gameState);

int *getCardValues(int count) {
    int *values = new int[count];
    int input;
    for (int i = 0; i < count; i++) {
        scanf("%i", &input);
        values[i] = input;
    }
    return values;
}

Settings getSettings() {
    int n, k, g, gv, o, e;
    scanf("%i %i %i %i %i %i", &n, &k, &g, &gv, &o, &e);
    return {
            n, k, g, gv, o, g + k * o, e, 0
    };
}
void dumb(GameState* gameState){
    gameState->Play(0);
}

void highestCardCount(GameState* gameState){
    Deck* deck = gameState->GetActivePlayerDeck();
    Deck* hand = gameState->GetActiveHand();

    int maxCards = 0;
    int maxCardsIndex = -1;
    int cardIndex = -1;

    for(int i = 0; i < gameState->GetPileCount();i++){
        if(gameState->GetPile(i)->GetContainedColor() <= 0)continue;
        int count = gameState->GetPile(i)->GetNonGreenCardCount() + deck->GetColorCount(gameState->GetPile(i)->GetContainedColor());
        if(count > maxCards){
            int explosionCost = gameState->GetExplosionThreshold() - gameState->GetPile(i)->GetCardsValue();
            int explosionColor = gameState->GetPile(i)->GetContainedColor();
            for(int j = 0; j < hand->GetCardsCount(); j++){
                if((hand->PeekCard(j).color == GREEN || hand->PeekCard(j).color == explosionColor) && hand->PeekCard(j).value >= explosionCost){
                    maxCards = count;
                    maxCardsIndex = i;
                    cardIndex = j;
                }
            }
        }
    }
    gameState->Play(cardIndex, maxCardsIndex);
}

void avoidExplosion(GameState* gameState){
    Deck* hand = gameState->GetActiveHand();
    for(int i = 0; i < hand->GetCardsCount();i++){
        for(int j = 0 ; j < gameState->GetPileCount(); j++){
            Card card = hand->PeekCard(i);
            if(card.value + gameState->GetPile(j)->GetCardsValue() < gameState->GetExplosionThreshold()){
                if(card.color == GREEN){
                    gameState->Play(i,j);
                    return;
                }
                if(card.color == gameState->GetPile(j)->GetContainedColor()){
                    gameState->Play(i,j);
                    return;
                }
            }
        }
    }
    highestCardCount(gameState);
}

void highestCard(GameState* gameState){
    Deck* deck = gameState->GetActiveHand();
    int maxIndex = -1;
    int max = MAX_VALUE;
    int minPile = -1;
    int maxCount = MAX_VALUE * MAX_CARDS_ON_HAND;
    for(int i = 0; i < deck->cardNumber;i++){
        int value = deck->PeekCard(i).value;
        if(value > max){
            max = value;
            maxIndex = i;

            Deck* pile = gameState->GetPileWithColor(deck->PeekCard(i).color);
            if(pile != nullptr){
                maxCount = pile->GetCardsCount();
                minPile = gameState->GetPileIdWithColor(deck->PeekCard(i).color);
            }else{
                for(int j = 0; j < gameState->GetPileCount();j++){
                    int v = gameState->GetPile(j)->GetCardsCount();
                    if(maxCount > v){
                        maxCount = v;
                        minPile = j;
                    }
                }
            }
        }
        if(value == max){
            int newPile = -1;
            int newCount = MAX_VALUE * MAX_CARDS_ON_HAND;
            Deck* pile = gameState->GetPileWithColor(deck->PeekCard(i).color);
            if(pile != nullptr){
                newCount = pile->GetCardsCount();
                newPile = gameState->GetPileIdWithColor(deck->PeekCard(i).color);
            }else{
                for(int j = 0; j < gameState->GetPileCount();j++){
                    int v = gameState->GetPile(j)->GetCardsCount();
                    if(newCount > v){
                        newCount = v;
                        newPile = j;
                    }
                }
            }
            if(newCount < maxCount){
                maxIndex = i;
                minPile = newPile;
                maxCount = newCount;
            }
        }
    }

    gameState->Play(maxIndex, minPile);
}

void optimalCard(GameState* gameState){
    Deck* deck = gameState->GetActiveHand();
    int max = 0;
    int maxIndex = -1;
    for(int i =0; i < deck->cardNumber; i++){
        int value = deck->PeekCard(i).value;
        if(value >= max){
            max = value;
            int minPile = -1;
            int minValue = MAX_VALUE * MAX_CARDS_ON_HAND;
            Deck* pile = gameState->GetPileWithColor(deck->PeekCard(i).color);
            if(pile != nullptr){
                minPile = gameState->GetPileIdWithColor(deck->PeekCard(i).color);
            }else{
                for(int j = 0; j < gameState->GetPileCount();j++){
                    int v = gameState->GetPile(j)->GetCardsValue();
                    if(minValue > v){
                        minValue = v;
                        minPile = j;
                    }
                }
            }
            if(gameState->GetPile(minPile)->GetCardsValue() + deck->PeekCard(i).value > gameState->GetExplosionThreshold()){
                continue;
            }else{
                gameState->Play(maxIndex,minPile);
                return;
            }
        }
    }
    highestCard(gameState);
}

void lowestCard(GameState* gameState){
    Deck* deck = gameState->GetActiveHand();
    int minIndex = -1;
    int min = MAX_VALUE;
    int minPile = -1;
    int minValue = MAX_VALUE * MAX_CARDS_ON_HAND;
    for(int i = 0; i < deck->cardNumber;i++){
        int value = deck->PeekCard(i).value;
        if(value < min){
            min = value;
            minIndex = i;

            Deck* pile = gameState->GetPileWithColor(deck->PeekCard(i).color);
            if(pile != nullptr){
                minValue = pile->GetCardsValue();
                minPile = gameState->GetPileIdWithColor(deck->PeekCard(i).color);
            }else{
                for(int j = 0; j < gameState->GetPileCount();j++){
                    int v = gameState->GetPile(j)->GetCardsValue();
                    if(minValue > v){
                        minValue = v;
                        minPile = j;
                    }
                }
            }
        }
        if(value == min){
            int newPile = -1;
            int newValue = MAX_VALUE*MAX_CARDS_ON_HAND;
            Deck* pile = gameState->GetPileWithColor(deck->PeekCard(i).color);
            if(pile != nullptr){
                newValue = pile->GetCardsValue();
                newPile = gameState->GetPileIdWithColor(deck->PeekCard(i).color);
            }else{
                for(int j = 0; j < gameState->GetPileCount();j++){
                    int v = gameState->GetPile(j)->GetCardsValue();
                    if(newValue > v){
                        newValue = v;
                        newPile = j;
                    }
                }
            }
            if(newValue < minValue){
                minIndex = i;
                minPile = newPile;
                minValue = newValue;
            }
        }
    }
    if(gameState->GetPile(minPile)->GetCardsValue() + gameState->GetActiveHand()->PeekCard(minIndex).value > gameState->GetExplosionThreshold()){
        highestCard(gameState);
        return;
    }
    gameState->Play(minIndex,minPile);
}
void play(GameState* gameState) {
    lowestCard(gameState);
    freopen("gameState.txt", "w", stdout);
    gameState->DisplayState();
    fclose(stdout);
    if (gameState->IsGameOver() == 1) {
        freopen("finalScore.txt", "w", stdout);
        gameState->DisplayScore();
    }
}

GameState* generateState() {
    freopen("gameState.txt", "w", stdout);
    Settings settings = getSettings();
    int *values = getCardValues(settings.cardCount);
    auto* gameState = new GameState(settings, new Deck(settings, values));
    delete[] values;
    gameState->DisplayState();
    return gameState;
}
void validateState(GameState* gameState){
    freopen("validationResult.txt", "w", stdout);
    gameState->DisplayValidationResult();
}
int main(int argc, char **argv) {
    GameState *gameState;
    if (argc == 2) {
        if (argv[1][0] == 'g') {
            gameState = generateState();
        }
        if (argv[1][0] == 'v') {
            gameState = StateParser::ReadFromStream();
            validateState(gameState);
        }
    } else {
        gameState = StateParser::ReadFromStream();
        play(gameState);
    }
    fclose(stdout);
    delete gameState;
    return 0;
}
