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
void lowestCard(GameState* gameState){

}
void play(GameState* gameState) {
    dumb(gameState);
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
