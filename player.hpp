#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include <vector>
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
    Move *minimaxChooseMove(int msLeft);
    vector<Move*> listMoves(Board * board);


    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;

private:
	Side side;
};

struct Node {
    Node();
    ~Node();

    Board *board = nullptr;
    Move *move = nullptr;
    vector<Move*> childrenMoves;
    int score = 0;
};

#endif
