#include "Players.h"
void Players::dumb(GameState* gameState){
    gameState->Play(0);
}

void Players::highestCardCount(GameState* gameState){
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

void Players::avoidExplosion(GameState* gameState){
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
    Players::highestCardCount(gameState);
}

void getPileWithHighestNumberOfColorCards(GameState* gameState, int color, int* count, int* pileNumber){
    Deck* pile = gameState->GetPileWithColor(color);
    if(pile != nullptr){
        *count = pile->GetCardsCount();
        *pileNumber = gameState->GetPileIdWithColor(color);
    }else{
        for(int j = 0; j < gameState->GetPileCount();j++){
            int v = gameState->GetPile(j)->GetCardsCount();
            if(*count > v){
                *count = v;
                *pileNumber = j;
            }
        }
    }
}

void Players::highestCard(GameState* gameState){
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
            getPileWithHighestNumberOfColorCards(gameState, deck->PeekCard(i).color, &maxCount, &minPile);
        }
        if(value == max){
            int newPile = -1;
            int newCount = MAX_VALUE * MAX_CARDS_ON_HAND;

            getPileWithHighestNumberOfColorCards(gameState, deck->PeekCard(i).color, &newCount, &newPile);
            if(newCount < maxCount){
                maxIndex = i;
                minPile = newPile;
                maxCount = newCount;
            }
        }
    }
    gameState->Play(maxIndex, minPile);
}

void Players::optimalCard(GameState* gameState){
    Deck* deck = gameState->GetActiveHand();
    int max = 0;
    int maxIndex = -1;
    int minPile = -1;
    for(int i =0; i < deck->GetCardsCount(); i++){
        int value = deck->PeekCard(i).value;
        if(value >= max){
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
                max = value;
            }
        }
    }
    if(maxIndex == -1 || minPile == -1)
        Players::highestCard(gameState);
    else
        gameState->Play(maxIndex, minPile);
}

void Players::lowestCard(GameState* gameState){
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
        Players::highestCard(gameState);
        return;
    }
    gameState->Play(minIndex,minPile);
}