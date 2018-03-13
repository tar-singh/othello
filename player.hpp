#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include <vector>
#include "common.hpp"
#include "board.hpp"
using namespace std;

class Node {

public:

	Node(Move *move) {
		this->move = move;
	};
	~Node() {
		delete board;
		delete move;
	};
    Board *board = nullptr;
    Move *move;
    vector<Move*> childrenMoves;
    int alpha = -1e8;
    int beta = 1e8;
    int score = -1e8;
    int level = 0;
    Side nodeSide;
    Move *bestMove = nullptr;
    Node *parent = nullptr;

};

class Player {

public:
    Player(Side side);
    ~Player();
    Board * B;

    Move *doMove(Move *opponentsMove, int msLeft);
    Move *randomMove(int msLeft);
    Move *basicHeuristicMove(Side side, int msLeft);
    Move *minimaxMove(Move *opponentsMove, int msLeft);
    Move *minimaxHeuristicMove(Move *opponentsMove, int msLeft);
    vector<Move*> listMoves(Board * board, Side side);
    Node *alphaBetaMove(Node *node, int msLeft);



    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
    bool testingHeuristicMinimax;

    bool runningAlphaBeta;

private:
	Side side;
};

#endif
