#include <iostream>
#include "statics.h"
#include "Deck.h"

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
    int k,g,gv,o;
    std::cin>>k>>g>>gv>>o;
    return {
            k,g,gv,o,g+k*o
    };
}

int main() {
    Settings settings = getSettings();
    int* values = getCardValues(settings.cardCount);

    Deck deck(settings, values);
    delete [] values;

    deck.DisplayDeck();



    return 0;
}
