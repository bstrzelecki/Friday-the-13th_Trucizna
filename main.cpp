#include <cstdio>
#include <ctime>
#include <cstdlib>
#include "statics.h"
#include "GameState.h"
#include "StateParser.h"
#include "Players.h"

void play(GameState* gameState) {


    void (*playerAction[])(GameState*) = {
        Players::optimalCard,
        Players::avoidExplosion,
        Players::lowestCard,
        Players::dumb,
        Players::lowestCard,
        Players::lowestCard,
        Players::lowestCard,
        Players::dumb
    };
    playerAction[gameState->GetActivePlayer()](gameState);
}

GameState* generateState(Settings settings, int* values) {
    auto* gameState = new GameState(settings, new Deck(settings, values));
    return gameState;
}

void autoPlay(Settings settings){
    GameState *gameState;
    int *values = StateParser::GetCardValues(settings.cardCount);
    int* winners = new int[settings.players];
    for(int i = 0; i < settings.players; i++){
        winners[i] = 0;
    }
    for(int t = 0; t < settings.games; t++){
        int* scores = new int[settings.players];
        for(int i = 0; i < settings.players; i++){
            scores[i] = 0;
        }
        for(int i = 0; i < settings.players; i++){
            gameState = generateState(settings, values);
            gameState->AdvanceActivePlayer(i);
            gameState->DisplayState();
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

// g - generates GameState and saves it as gameState.txt
// v - validates validates given GameState and saves results in validationResult.txt
// a - executes multiple games and saves results to gameLog.txt
int main(int argc, char **argv) {
    srand(time(nullptr));
    if(argc > 2){
        freopen(argv[1], "r", stdin);
        GameState* gameState = StateParser::ReadFromStream();
        Players::optimalCard(gameState);
        freopen(argv[1], "w", stdout);
        gameState->DisplayState();
        delete gameState;
    }
    else if (argc == 2) {
        if (argv[1][0] == 'g') {
            freopen(STATE_FILE, "w", stdout);
            const Settings settings = StateParser::GetSettingsFromStream();
            GameState *gameState;
            int *values = StateParser::GetCardValues(settings.cardCount);
            gameState = generateState(settings, values);
            gameState->DisplayState();
            delete[] values;
            delete gameState;
        }
        if (argv[1][0] == 'v') {
            GameState *gameState;
            gameState = StateParser::ReadFromStream();
            freopen(VALIDATION_OUTPUT_FILE, "w", stdout);
            gameState->DisplayValidationResult();
            delete gameState;
        }
        if(argv[1][0] == 'a'){
            const Settings settings = StateParser::GetSettingsFromStream();
            freopen(LOG_FILE, "a", stdout);
            autoPlay(settings);
        }
    }else {
        GameState *gameState;
        gameState = StateParser::ReadFromStream();
        freopen(STATE_FILE, "w", stdout);
        play(gameState);
        gameState->DisplayState();
        if(gameState->IsGameOver() == 1){
            freopen(SCORE_FILE, "w", stdout);
            gameState->DisplayScore();
        }
        delete gameState;
    }
    fclose(stdout);
    return 0;
}
