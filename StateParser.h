#ifndef POP202_1_STATEPARSER_H
#define POP202_1_STATEPARSER_H


#include "GameState.h"

class StateParser {
public:
    static GameState *ReadFromStream();
    static int* GetCardValues(int count);
    static Settings GetSettingsFromStream();
    static Settings GetSettingsFromArgs(char **argv);
};


#endif
