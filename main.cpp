#include <iostream>
#include "statics.h"
#include "GameState.h"
#include "StateParser.h"
int* getCardValues(int count){
    int* values = new int[count];
    int input;
    for(int i = 0; i < count; i++){
        std::cin>>input;
        values[i] = input;
    }
    return values;
}
Settings getSettings(){
    int n,k,g,gv,o;
    std::cin>>n>>k>>g>>gv>>o;
    return {
            n,k,g,gv,o,g+k*o
    };
}

int main() {
    //Settings settings = getSettings();
    //int* values = getCardValues(settings.cardCount);

    //Deck deck(settings, values);
    //delete [] values;

    //GameState gameState(settings, deck);

    GameState gameState = StateParser::ReadFromStream();


    gameState.Play(0);
    gameState.DisplayState();
    /*
    VALIDATION_RESULT a = gameState.ValidateHands();
    VALIDATION_RESULT b = gameState.ValidatePiles();
    if(a==VALIDATION_SUCCESS&&b==VALIDATION_SUCCESS)
    {
        std::cout<<"Current state of the game is ok";
    }
     */
    return 0;
}
