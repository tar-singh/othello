#include "player.hpp"
 
/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;
    this->side = side;
    
    Board * board = new Board();

    Move a = Move(3, 3);
    Move b = Move(3, 4);
    Move c = Move(4, 3);
    Move d = Move(4, 4);

    b.doMove(&a0, WHITE);
    b.doMove(&b0, BLACK);
    b.doMove(&c0, BLACK);
    b.doMove(&d0, WHITE);
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

<<<<<<< HEAD
/*
Move *Player::chooseMove() {
    if Board::hasmoves(for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if Board::
        }
    }
*/
=======
/*Move *Player::chooseMove() {
    if (Board::hasmoves(for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if Board::
        }
    }*/

>>>>>>> 370004afd18bed3279a01dde01af1c9e1bd220be
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    
    return nullptr;

}



