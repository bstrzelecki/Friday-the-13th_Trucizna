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
    int n, k, g, gv, o, e, r, t;
    scanf("%i %i %i %i %i %i %i %i", &n, &k, &g, &gv, &o, &e, &r, &t);
    return {
            n, k, g, gv, o, g + k * o, e, 0, r, t
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
    int max = 0;
    int minPile = -1;
    int maxCount = MAX_VALUE * MAX_CARDS_ON_HAND;
    for(int i = 0; i < deck->GetCardsCount();i++){
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
    int minPile = -1;
    for(int i =0; i < deck->GetCardsCount(); i++){
        int value = deck->PeekCard(i).value;
        if(value >= max){
            max = value;
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
                maxIndex = i;
            }
        }
    }
    if(maxIndex == -1 || minPile == -1)
        highestCard(gameState);
    else
        gameState->Play(maxIndex, minPile);
}

void lowestCard(GameState* gameState){
    Deck* deck = gameState->GetActiveHand();
    int minIndex = -1;
    int min = MAX_VALUE;
    int minPile = -1;
    int minValue = MAX_VALUE * MAX_CARDS_ON_HAND;
    for(int i = 0; i < deck->GetCardsCount();i++){
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
    if((minIndex == -1 || minPile == -1) || gameState->GetPile(minPile)->GetCardsValue() + gameState->GetActiveHand()->PeekCard(minIndex).value > gameState->GetExplosionThreshold()){
        highestCard(gameState);
        return;
    }
    gameState->Play(minIndex,minPile);
}
void play(GameState* gameState) {


    void (*playerAction[])(GameState*) = {
        dumb,
        optimalCard,
        lowestCard,
        dumb,
        lowestCard,
        lowestCard,
        lowestCard,
        dumb
    };
    playerAction[gameState->GetActivePlayer()](gameState);
}

GameState* generateState(Settings settings, int* values) {
    auto* gameState = new GameState(settings, new Deck(settings, values));
    gameState->DisplayState();
    return gameState;
}
void validateState(GameState* gameState){
    gameState->DisplayValidationResult();
}

void autoPlay(Settings settings){
    GameState *gameState;
    int *values = getCardValues(settings.cardCount);
    int* winners = new int[settings.players];
    for(int i = 0; i < settings.players; i++){
        winners[i] = 0;
    }
    for(int t = 0; t < settings.games; t++){
        int* scores = new int[settings.players];
        for(int i = 0; i < settings.players; i++){
            scores[i] = 0;
        }
        int roundCounter = settings.rounds;
        for(int i = roundCounter; i > 0; i--){
            gameState = generateState(settings, values);
            while(gameState->IsGameOver() == 0){
                gameState->DisplayValidationResult();
                play(gameState);
                gameState->DisplayState();
            }
            gameState->DisplayScore();
            for(int j = 0; j < settings.players; j++){
                scores[j] += gameState->GetPlayerScore(j);
            }
            delete gameState;
        }
        int min = MAX_VALUE*MAX_CARDS_ON_HAND;
        for(int i = 0; i < settings.players; i++){
            if(scores[i] < min){
                min = scores[i];
            }
        }
        for(int i = 0; i < settings.players; i++){
            printf("Player %i has %i points.\n", i+1, scores[i]);
        }
        for(int i = 0; i < settings.players;i++){
            if(scores[i] == min){
                winners[i]++;
                printf("Player %i won!\n", i+1);
            }

        }
        delete [] scores;
    }
    printf("Final results:\n");
    for(int i = 0; i < settings.players; i++){
        printf("Player %i won %i times.\n",i+1,winners[i]);
    }
    delete[] values;
    delete[] winners;
}

int main(int argc, char **argv) {
    if (argc == 2) {
        if (argv[1][0] == 'g') {
            GameState *gameState;
            freopen("gameState.txt", "w", stdout);
            const Settings settings = getSettings();
            int *values = getCardValues(settings.cardCount);
            gameState = generateState(settings, values);
            delete[] values;
            delete gameState;
        }
        if (argv[1][0] == 'v') {
            GameState *gameState;
            gameState = StateParser::ReadFromStream();
            freopen("validationResult.txt", "w", stdout);
            validateState(gameState);
            delete gameState;
        }
        if(argv[1][0] == 'a'){
            const Settings settings = getSettings();
            freopen("gameLog.txt", "a", stdout);
            autoPlay(settings);
        }
    }else {
        GameState *gameState;
        gameState = StateParser::ReadFromStream();
        freopen("gameState.txt", "w", stdout);
        play(gameState);
        gameState->DisplayState();
        if(gameState->IsGameOver() == 1){
            freopen("finalScore.txt", "w", stdout);
            gameState->DisplayScore();
        }
        delete gameState;
    }
    fclose(stdout);
    return 0;
}
