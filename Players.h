//
// Created by mabat on 03/12/2020.
//

#ifndef POP202_1_PLAYERS_H
#define POP202_1_PLAYERS_H


#include "GameState.h"

class Players {
public:
    static void dumb(GameState* gameState);
    static void highestCardCount(GameState* gameState);
    static void avoidExplosion(GameState* gameState);
    static void highestCard(GameState* gameState);
    static void optimalCard(GameState* gameState);
    static void lowestCard(GameState* gameState);
};


#endif //POP202_1_PLAYERS_H
