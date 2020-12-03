cmake_minimum_required(VERSION 3.17)
project(POP202_1)

set(CMAKE_CXX_STANDARD 20)

add_executable(POP202_1 main.cpp Deck.cpp Deck.h statics.h GameState.cpp GameState.h StateParser.cpp StateParser.h Players.cpp Players.h)