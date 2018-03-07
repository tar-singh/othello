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
    Move *basicHeuristicMove(Side side, int msLeft);
    Move *minimaxMove(Move *opponentsMove, Side side, int msLeft);
    vector<Move*> listMoves(Board * board, Side side);


    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;

    bool testingRandom;

private:
	Side side;
};

class Node {

public:

	Node(Move *move) {
		this->move = move;
	};
    Board *board = nullptr;
    Move * move;
    vector<Move*> childrenMoves;

};

#endif
