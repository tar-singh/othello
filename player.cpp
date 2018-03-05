#include "player.hpp"
 
/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;

    Board b = Board();
    Move a0 = Move(3, 3);
    Move b0 = Move(3, 4);
    Move c0 = Move(4, 3);
    Move d0 = Move(4, 4);
    Side white = Side::WHITE;
    Side black = Side::BLACK;

    b.doMove(&a0, white);
    b.doMove(&b0, black);
    b.doMove(&c0, black);
    b.doMove(&d0, white);
    /*
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */
}

/*
 * Destructor for the player.
 */
Player::~Player() {
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be
 * nullptr.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return nullptr.
 */

Move *Player::chooseMove() {
    if Board::hasmoves(for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if Board::
        }
    }
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    
    return nullptr;
}


