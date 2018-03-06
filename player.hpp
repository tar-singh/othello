#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.hpp"
#include "board.hpp"
using namespace std;

class Player {

public:
    Player(Side side);
    ~Player();
    Board * B;

    Move *doMove(Move *opponentsMove, int msLeft);
    Move *randomMove(int msLeft);


    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;

private:
	Side side;
};

#endif
