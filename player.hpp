#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.hpp"
#include "board.hpp"
using namespace std;

class Player {

public:
	Board * B = new Board();
    Player(Side side);
    ~Player();

    Move *doMove(Move *opponentsMove, int msLeft, Side side);


    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
};

#endif
