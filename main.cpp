#include <iostream>
#include "statics.h"
#include "GameState.h"
#include "StateParser.h"
#include <fstream>

int *getCardValues(int count) {
    int *values = new int[count];
    int input;
    for (int i = 0; i < count; i++) {
        std::cin >> input;
        values[i] = input;
    }
    return values;
}

Settings getSettings() {
    int n, k, g, gv, o, e;
    std::cin >> n >> k >> g >> gv >> o>> e;
    return {
            n, k, g, gv, o, g + k * o, e, 0
    };
}

int main(int argc, char** argv) {
    if(argc == 2){
        if(argv[1][0] == 'g'){
            std::fstream file;
            file.open("gameState.txt", std::ios::out);
            std::cout.rdbuf(file.rdbuf());
            Settings settings = getSettings();
            int* values = getCardValues(settings.cardCount);
            Deck deck(settings, values);
            delete [] values;
            GameState gameState(settings, deck);
            gameState.DisplayState();
            file.close();
        }
        if(argv[1][0] == 'v'){
            GameState gameState = StateParser::ReadFromStream();
            std::fstream file;
            file.open("validationResult.txt", std::ios::out);
            std::cout.rdbuf(file.rdbuf());
            gameState.DisplayValidationResult();
        }
    }else{
        GameState gameState = StateParser::ReadFromStream();
        gameState.Play(0);
        std::fstream file;
        file.open("gameState.txt", std::ios::out);
        std::cout.rdbuf(file.rdbuf());
        gameState.DisplayState();
        file.close();
        if(gameState.IsGameOver() == 1){;
            file.open("finalScore.txt", std::ios::out);
            std::cout.rdbuf(file.rdbuf());
            gameState.DisplayScore();
            file.close();
        }
    }
    return 0;
}
