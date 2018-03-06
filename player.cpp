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
 * just chooses some random move, unsure about parameters
*/
Move *Player::randomMove(int msLeft) {
    Move *m = new Move(0, 0);

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

vector<Move*> Player::listMoves(Board * board) {
    vector<Move*> movesList;
    if (board->hasMoves(side)) {
        for (int i = 0; i < 8; i++){
            for (int j = 0; j < 8; j++){
                Move *m = new Move(i, j);
                if (board->checkMove(m, side)){
                    movesList.push_back(m);
                }
            }
        }
    }
    return movesList;
}

Move *Player::minimaxChooseMove(int msLeft) {
    //make tree with nodes with tons of prob unnecessary stuff
    int totalScore = 0;
    int maxScore = -1000000;
    Move *bestMove = nullptr;
    Side other;
    if (side == BLACK) {
        other = WHITE;
    }
    else if (side == WHITE) {
        other = BLACK;
    }

    //make grandma node!
    vector<Node*> nodesList;
    Node *node0 = new Node();
    node0->board = B->copy();
    for (unsigned int j = 0; j < listMoves(node0->board).size(); j++) {
        node0->childrenMoves.push_back(listMoves(node0->board)[j]);
    }
    nodesList.push_back(node0);

    //we move first
    for (unsigned int i = 0; i < (node0->childrenMoves).size(); i++) {
        Node *node1 = new Node();
        node1->board = node0->board->copy();
        node1->move = node0->childrenMoves[i];
        node1->score = node1->board->score(node1->move, side);
        node1->board->doMove(node1->move, side);
        for (unsigned int k = 0; k < listMoves(node1->board).size(); k++) {
            node1->childrenMoves.push_back(listMoves(node1->board)[k]);
        }
        nodesList.push_back(node1);

        //their move
        int minScore = 1000000;
        for (unsigned int l = 0; l < (node1->childrenMoves).size(); l++) {
            if (node1->board->score(node1->childrenMoves[l], side) < minScore) {
                if (node1->board->score(node1->childrenMoves[l], side) + node1->score > maxScore){
                    maxScore = totalScore + node1->score;
                    bestMove = node1->move;
                }
            }
        }
    }

    //delete stuff
    for (unsigned int m = 0; m < nodesList.size(); m++) {
        delete nodesList[m];
    }

    return bestMove;
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
 * 
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    Move * m = new Move(0, 0);
    Move * move = new Move(0, 0);
    Side other;
    int temp;
    int total = 0;

    //record opponents move
    if (side == BLACK){
        other = WHITE;
    }
    else if (side == WHITE){
        other = BLACK;
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
                    std::cerr << "i: " << i << std::endl;
                    std::cerr << "j: " << j << std::endl;
                    std::cerr << "help" << std::endl;
                    temp = B->score(m, side);
                    if (temp > total)
                    {
                        total = temp;
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
}

