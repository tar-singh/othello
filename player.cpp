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
    testingHeuristicMinimax = false;
    runningAlphaBeta = false;

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
    bool validMove = false;
    int temp;
    int total = -100000;
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



Move *Player::minimaxMove(Move *opponentsMove, int msLeft) {
    int newScore;
    int maxScore = -1000000;
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
                maxScore = node1->board->countBlack() - node1->board->countWhite();
                bestMove = node1->move;
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
                    node2->board->doMove(node2->move, WHITE);
                    newScore = node2->board->countBlack() - node2->board->countWhite();
                    if (newScore < branchScore){
                        branchScore = newScore;
                    }
                }
                if (branchScore > maxScore){
                    maxScore = branchScore;
                    bestMove = node1->move;
                }    
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
                maxScore = node1->board->countWhite() - node1->board->countBlack();
                bestMove = node1->move;
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
                if (branchScore > maxScore){
                    maxScore = branchScore;
                    bestMove = node1->move;
                }    
            }
        }
    }

    B->doMove(bestMove, side);
    
    //delete stuff
    /*for (unsigned int m = 0; m < nodesList.size(); m++) {
        delete nodesList[nodesList.size() - m - 1]->board;
        if (nodesList[nodesList.size() - m - 1]->childrenMoves.size() > 0) {
            for (unsigned int x = 0; x < nodesList[nodesList.size() - m - 1]->childrenMoves.size(); x++) {
                delete (nodesList[nodesList.size() - m - 1]->childrenMoves)[x];
            }
        }
    }
    for (unsigned int y = 0; y < nodesList.size(); y++) {
        delete nodesList[y];
    }*/

    return bestMove;
}


Move *Player::minimaxHeuristicMove(Move *opponentsMove, int msLeft) {
    int newScore;
    int maxScore = -1000000;
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
                maxScore = node0->board->score(node1->move, BLACK);
                bestMove = node1->move;
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
                    node2->board->doMove(node2->move, WHITE);
                    newScore = -1 * node1->board->score(node2->move, WHITE);
                    if (newScore < branchScore){
                        branchScore = newScore;
                    }
                }
                if (branchScore > maxScore){
                    maxScore = branchScore;
                    bestMove = node1->move;
                }    
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
                maxScore = node0->board->score(node1->move, WHITE);
                bestMove = node1->move;
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
                    newScore = -1 * node1->board->score(node2->move, BLACK);
                    if (newScore < branchScore){
                        branchScore = newScore;
                    }
                }
                if (branchScore > maxScore){
                    maxScore = branchScore;
                    bestMove = node1->move;
                }    
            }
        }
    }

    B->doMove(bestMove, side);
    
    //delete stuff
    /*for (unsigned int m = 0; m < nodesList.size(); m++) {
        delete nodesList[nodesList.size() - m - 1]->board;
        if (nodesList[nodesList.size() - m - 1]->childrenMoves.size() > 0) {
            for (unsigned int x = 0; x < nodesList[nodesList.size() - m - 1]->childrenMoves.size(); x++) {
                delete (nodesList[nodesList.size() - m - 1]->childrenMoves)[x];
            }
        }
    }
    for (unsigned int y = 0; y < nodesList.size(); y++) {
        delete nodesList[y];
    }*/

    return bestMove;
}


vector<Node*> nodesVector;
Node *Player::alphaBetaMove(Node *node, int msLeft) {
    // determine side of other
    Side other;
    if (side == BLACK){ 
        other = WHITE;
    }
    else if (side == WHITE){
        other = BLACK;
    }

    // if it reaches the bottom
    if (node->level == 4 || listMoves(node->board, node->nodeSide).size() <= 0) {
        //determine score
        node->score = node->board->countBlack() - node->board->countWhite();
        if (node->nodeSide == WHITE) {
            node->score *= -1;
        }
        return node;
    }
    else {
        // i don't think it needs childrenMoves but i'll keep it here until i finish 
        // maybe delete later
        for (unsigned int j = 0; j < listMoves(node->board, node->nodeSide).size(); j++) {
            node->childrenMoves.push_back(listMoves(node->board, node->nodeSide)[j]);
        }

        // create new children moves and start recursion
        if (node->alpha <= node->beta) {
            for (unsigned int i = 0; i < node->childrenMoves.size(); i++) {
                Node *node1 = new Node(node->childrenMoves[i]);
                // determine nodeSide, level, and score
                node1->board = node->board->copy();
                node1->board->doMove(node1->move, node->nodeSide);
                node1->level = node->level + 1;
                node1->alpha = node->alpha;
                node1->beta = node->beta;
                if (node->nodeSide == side) {
                    node1->nodeSide = other;
                    node1->score = 1e8;
                }
                else if (node->nodeSide == other) {
                    node1->nodeSide = side;
                    node1->score = -1e8;
                }
                node1->parent = node;
                std::cerr << std::endl;
                std::cerr << "another" << std::endl;
                std::cerr << "node move: " << node1->move->getX() << "," << node1->move->getY() << std::endl;
                std::cerr << "nodeSide: " << node1->nodeSide << std::endl;
                std::cerr << "level: " << node1->level << std::endl;
                std::cerr << "alpha: " << node1->alpha << std::endl;
                std::cerr << "beta: " << node1->beta << std::endl;
                nodesVector.push_back(node1);
                Node *newNode = alphaBetaMove(node1, msLeft);

                // starts going back up tree to determine new alpha/beta values
                if (newNode->nodeSide == side) {
                    if (newNode->score <= newNode->parent->score) {
                        newNode->parent->score = newNode->score;
                        newNode->parent->bestMove = newNode->move;
                    }
                    if (newNode->score <= newNode->parent->beta) {
                        newNode->parent->beta = newNode->score;
                    }
                }
                else if (newNode->nodeSide == other) {
                    if (newNode->score >= newNode->parent->score) {
                        newNode->parent->score = newNode->score;
                        newNode->parent->bestMove = newNode->move;
                    }
                    if (newNode->score >= newNode->parent->alpha) {
                        newNode->parent->alpha = newNode->score; 
                    }
                }
                std::cerr << std::endl;
                std::cerr << "new set" << std::endl;
                std::cerr << "node side: " << newNode->nodeSide << std::endl;
                std::cerr << "node score: " << newNode->score << std::endl;
                std::cerr << "node level: " << newNode->level << std::endl;
                std::cerr << "node move: " << newNode->move->getX() << "," << newNode->move->getY() << std::endl;
                std::cerr << "node alpha: " << newNode->alpha << std::endl;
                std::cerr << "node beta: " << newNode->beta << std::endl;
                std::cerr << std::endl;
                std::cerr << "parent node side: " << newNode->parent->nodeSide << std::endl;
                std::cerr << "parent node score: " << newNode->parent->score << std::endl;
                std::cerr << "parent node level: " << newNode->parent->level << std::endl;
                std::cerr << "parent node bestMove: " << newNode->parent->bestMove->getX() << "," <<newNode->parent->bestMove->getY() << std::endl;
                std::cerr << "alpha: " << newNode->parent->alpha << std::endl;
                std::cerr << "beta: " << newNode->parent->beta << std::endl;
            }
        }
    }
    if (node->level == 0) {
        return node;
    }
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
    runningAlphaBeta = true;

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
        return minimaxMove(opponentsMove, msLeft);
    }
    else if (testingHeuristicMinimax == true) {
        return minimaxHeuristicMove(opponentsMove, msLeft);
    }
    else if (runningAlphaBeta == true) {
        Node *node0 = new Node(opponentsMove);
        node0->board = B->copy();
        node0->nodeSide = side;
        nodesVector.push_back(node0);
        Move *bestMove = alphaBetaMove(node0, msLeft)->bestMove;
        B->doMove(bestMove, side);
        return bestMove;
    }

    // do and return random move
    // uncomment to run
    // return randomMove(msLeft);

    // do and return basic heuristic move
    // comment out basicHeuristicMove to run random move
    return basicHeuristicMove(side, msLeft);

}

