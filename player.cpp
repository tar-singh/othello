#include "player.hpp"
#include <thread>
#include <chrono>

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;

    this->side = side;
    Board * B = new Board();
    this->B = B;

    Move a = Move(3, 3);
    Move b = Move(3, 4);
    Move c = Move(4, 3);
    Move d = Move(4, 4);

    B->doMove(&a, WHITE);
    B->doMove(&b, BLACK);
    B->doMove(&c, BLACK);
    B->doMove(&d, WHITE);

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
    delete B;
}

/*
 * just chooses some random move
 * unsure about parameters
*/
Move *Player::randomMove(int msLeft) {
    Move *m = new Move(0, 0);
    int score;

    if (B->hasMoves(side)) {
        for (int i = 0; i < 8; i++){
            for (int j = 0; j < 8; j++){
                *m = Move(i, j);
                if (B->checkMove(m, side)){
                    B->doMove(m, side);
                    return m;
                }
            }
        }
    }
    delete m;
    return nullptr;
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
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    Move * m = new Move(0, 0);
    Move * move = new Move(0, 0);
    Side other;
    int temp;
    int score;

    //record opponents move
    if (side == BLACK){
        other = WHITE;
        count = B->countBlack();
    }
    else if (side == WHITE){
        other = BLACK;
        count = B->countWhite();
    }
    if (opponentsMove != nullptr){
        B->doMove(opponentsMove, other);
    }


    if (B->hasMoves(side)){
        for (int i = 0; i < 8; i++){
            for (int j = 0; j < 8; j++){
                *m = Move(i, j);
                if (B->checkMove(m, side)){
                    // std::this_thread::sleep_for(std::chrono::seconds(5));
                    temp = score(m, side);
                    if (temp > score)
                    {
                        score = temp;
                        *move = Move(i, j);
                    }
                }
            }
        }
    }

    B->doMove(move, side);
    return move;


    delete m;
    delete move;
    return nullptr;

    //do and return random move
    return randomMove(msLeft);
}

