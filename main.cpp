#include <cstdio>
#include "statics.h"
#include "GameState.h"
#include "StateParser.h"
#include <fstream>

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

void play(GameState *state) {

}

int main(int argc, char **argv) {
    GameState *gameState;
    if (argc == 2) {
        if (argv[1][0] == 'g') {
            freopen("gameState.txt", "w", stdout);
            Settings settings = getSettings();
            int *values = getCardValues(settings.cardCount);
            gameState = new GameState(settings, new Deck(settings, values));
            delete[] values;
            gameState->DisplayState();
        }
        if (argv[1][0] == 'v') {
            gameState = StateParser::ReadFromStream();
            freopen("validationResult.txt", "w", stdout);
            gameState->DisplayValidationResult();
        }
    } else {
        gameState = StateParser::ReadFromStream();
        gameState->Play(0);
        freopen("gameState.txt", "w", stdout);
        gameState->DisplayState();
        fclose(stdout);
        if (gameState->IsGameOver() == 1) { ;
            freopen("finalScore.txt", "w", stdout);
            gameState->DisplayScore();
        }
    }
    fclose(stdout);
    delete gameState;
    return 0;
}
