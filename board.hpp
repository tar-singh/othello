#ifndef __BOARD_H__
#define __BOARD_H__

#include <bitset>
#include "common.hpp"
#include <iostream>
using namespace std;

class Board {

private:
    bitset<64> black;
    bitset<64> taken;


public:
    Board();
    ~Board();
    Board *copy();
    
    bool occupied(int x, int y);
    bool get(Side side, int x, int y);
    void set(Side side, int x, int y);
    bool onBoard(int x, int y);
    bool isDone();
    bool hasMoves(Side side);
    bool checkMove(Move *m, Side side);
    void doMove(Move *m, Side side);
    int count(Side side);
    int countBlack();
    int countWhite();
    void setBoard(char data[]);
    int score(Move *m, Side side);
    int countFlipped(Move *m, Side side);
    int betterScore(Move *m, Side side);
    int getQuadrant(int X, int Y);
    bool getCorner(int quadrant, Side side);
    bool getEdge(int X, int Y);
    int getCreepingEdge(int X, int Y, Side side);
    bool getLastEdgePiece(int X, int Y, bool creepingEdgeBool, Side side);
};


#endif
