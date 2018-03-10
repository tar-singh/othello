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

Move *Player::basicHeuristicMove(Side side, int msLeft) {
    Move * m = new Move(0, 0);
    Move * move = new Move(0, 0);
    int temp;
    int total = -100000;
    bool validMove = false;
    if (B->hasMoves(side)){
        for (int i = 0; i < 8; i++){
            for (int j = 0; j < 8; j++){
                *m = Move(i, j);
                if (B->checkMove(m, side)){
                    temp = B->score(m, side);
                    if (temp > total)
                    {
                        total = temp;
                        *move = Move(i, j);
                        validMove = true;
                    }
                }
            }
        }
    }

    if (validMove) {
        B->doMove(move, side);
        return move;
    }

    delete m;
    delete move;
    return nullptr;    
}

vector<Move*> Player::listMoves(Board * board, Side side) {
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

Move *Player::minimaxMove(Move *opponentsMove, Side side, int msLeft) {
    int newScore;
    vector<int> branchScores;
    vector<Move*> bestMoves;
    Move *bestMove = nullptr;

    //make grandma node!
    vector<Node*> nodesList;
    Node *node0 = new Node(opponentsMove);
    node0->board = B->copy();

    //we move first
    if (side == BLACK) {
        //if no more moves after this one
        if (listMoves(node0->board, BLACK).size() <= 0) {
            return bestMove;
        }
        for (unsigned int j = 0; j < listMoves(node0->board, BLACK).size(); j++) {
            node0->childrenMoves.push_back(listMoves(node0->board, BLACK)[j]);
        }
        nodesList.push_back(node0);    
        for (unsigned int n = 0; n < (node0->childrenMoves).size(); n++) {
            Node *node1 = new Node(node0->childrenMoves[n]);
            node1->board = node0->board->copy();
            node1->board->doMove(node1->move, BLACK);
            if (listMoves(node1->board, WHITE).size() <= 0) {
                int maxScore = node1->board->countBlack() - node1->board->countWhite();
                branchScores.push_back(maxScore);
                nodesList.push_back(node1);
            }
            else {
                for (unsigned int q = 0; q < listMoves(node1->board, WHITE).size(); q++) {
                    node1->childrenMoves.push_back(listMoves(node1->board, WHITE)[q]);
                    nodesList.push_back(node1);
                }  
                //their move
                int branchScore = 1000000;
                for (unsigned int r = 0; r < (node1->childrenMoves).size(); r++) {
                    Node *node2 = new Node(node1->childrenMoves[r]);
                    node2->board = node1->board->copy();
                    node2->board->doMove(node2->move, BLACK);
                    newScore = node2->board->countBlack() - node2->board->countWhite();
                    if (newScore < branchScore){
                        branchScore = newScore;
                    }
                }
                branchScores.push_back(branchScore);
                std::cerr << std::endl;
                std::cerr << "minScore:" << branchScore << std::endl;
                bestMoves.push_back(node1->move);      
            }
        }
    }

    else if (side == WHITE) {
        //if no more moves after this one
        if (listMoves(node0->board, WHITE).size() <= 0) {
            return bestMove;
        }
        for (unsigned int j = 0; j < listMoves(node0->board, WHITE).size(); j++) {
            node0->childrenMoves.push_back(listMoves(node0->board, WHITE)[j]);
        }
        nodesList.push_back(node0);    
        for (unsigned int n = 0; n < (node0->childrenMoves).size(); n++) {
            Node *node1 = new Node(node0->childrenMoves[n]);
            node1->board = node0->board->copy();
            node1->board->doMove(node1->move, WHITE);
            if (listMoves(node1->board, BLACK).size() <= 0) {
                int maxScore = node1->board->countWhite() - node1->board->countBlack();
                branchScores.push_back(maxScore);
                nodesList.push_back(node1);
            }
            else {
                for (unsigned int q = 0; q < listMoves(node1->board, BLACK).size(); q++) {
                    node1->childrenMoves.push_back(listMoves(node1->board, BLACK)[q]);
                    nodesList.push_back(node1);
                }  
                //their move
                int branchScore = 1000000;
                for (unsigned int r = 0; r < (node1->childrenMoves).size(); r++) {
                    Node *node2 = new Node(node1->childrenMoves[r]);
                    node2->board = node1->board->copy();
                    node2->board->doMove(node2->move, BLACK);
                    newScore = node2->board->countWhite() - node2->board->countBlack();
                    if (newScore < branchScore){
                        branchScore = newScore;
                    }
                }
                branchScores.push_back(branchScore);
                std::cerr << std::endl;
                std::cerr << "minScore:" << branchScore << std::endl;
                bestMoves.push_back(node1->move);      
            }
        }
    }
    int bestMoveIndex = 0;
    for (unsigned int z = 0; z < branchScores.size(); z++) {
        if (branchScores[z] > branchScores[0]) {
            bestMoveIndex = z;
        }
    }


    //delete stuff
    /*for (unsigned int m = 0; m < nodesList.size(); m++) {
        delete nodesList[m];
    }*/

    B->doMove(bestMoves[bestMoveIndex], side);
    return bestMoves[bestMoveIndex];
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
    Side other;

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

    if (testingMinimax == true) {
        return minimaxMove(opponentsMove, side, msLeft);
    }

    // do and return random move
    // uncomment to run
    // return randomMove(msLeft);

    // do and return basic heuristic move
    // comment out basicHeuristicMove to run random move
    return basicHeuristicMove(side, msLeft);

}

