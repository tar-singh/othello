#include "board.hpp"


/*
 * Make a standard 8x8 othello board and initialize it to the standard setup.
 */
Board::Board() {
    taken.set(3 + 8 * 3);
    taken.set(3 + 8 * 4);
    taken.set(4 + 8 * 3);
    taken.set(4 + 8 * 4);
    black.set(4 + 8 * 3);
    black.set(3 + 8 * 4);
}

/*
 * Destructor for the board.
 */
Board::~Board() {
}

/*
 * Returns a copy of this board.
 */
Board *Board::copy() {
    Board *newBoard = new Board();
    newBoard->black = black;
    newBoard->taken = taken;
    return newBoard;
}

// returns if occupied by piece
bool Board::occupied(int x, int y) {
    return taken[x + 8*y];
}

// returns color of piece on board
bool Board::get(Side side, int x, int y) {
    return occupied(x, y) && (black[x + 8*y] == (side == BLACK));
}

// sets a piece on the board to a certain color
void Board::set(Side side, int x, int y) {
    taken.set(x + 8*y);
    black.set(x + 8*y, side == BLACK);
}

// if spot is on board
bool Board::onBoard(int x, int y) {
    return(0 <= x && x < 8 && 0 <= y && y < 8);
}


/*
 * Returns true if the game is finished; false otherwise. The game is finished
 * if neither side has a legal move.
 */
bool Board::isDone() {
    return !(hasMoves(BLACK) || hasMoves(WHITE));
}

/*
 * Returns true if there are legal moves for the given side.
 */
bool Board::hasMoves(Side side){
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Move move(i, j);
            if (checkMove(&move, side)) 
                {
                    return true;
                }
        }
    }
    return false;
}

/*
 * Returns true if a move is legal for the given side; false otherwise.
 */
bool Board::checkMove(Move *m, Side side) {
    // Passing is only legal if you have no moves.
    if (m == nullptr) return !hasMoves(side);

    int X = m->getX();
    int Y = m->getY();

    // Make sure the square hasn't already been taken.
    if (occupied(X, Y)) return false;

    Side other = (side == BLACK) ? WHITE : BLACK;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dy == 0 && dx == 0) continue;

            // Is there a capture in that direction?
            int x = X + dx;
            int y = Y + dy;
            if (onBoard(x, y) && get(other, x, y)) {
                do {
                    x += dx;
                    y += dy;
                } while (onBoard(x, y) && get(other, x, y));
                
                if (onBoard(x, y) && get(side, x, y)) return true;
            }
        }
    }
    return false;
}

/*
 * Modifies the board to reflect the specified move.
 */
void Board::doMove(Move *m, Side side) {
    // A nullptr move means pass.
    if (m == nullptr) return;

    // Ignore if move is invalid.
    if (!checkMove(m, side)) return;

    int X = m->getX();
    int Y = m->getY();
    Side other = (side == BLACK) ? WHITE : BLACK;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dy == 0 && dx == 0) continue;

            int x = X;
            int y = Y;
            do {
                x += dx;
                y += dy;
            } while (onBoard(x, y) && get(other, x, y));

            if (onBoard(x, y) && get(side, x, y)) {
                x = X;
                y = Y;
                x += dx;
                y += dy;
                while (onBoard(x, y) && get(other, x, y)) {
                    set(side, x, y);
                    x += dx;
                    y += dy;
                }
            }
        }
    }
    set(side, X, Y);
}

/*
 * Current count of given side's stones.
 */
int Board::count(Side side) {
    return (side == BLACK) ? countBlack() : countWhite();
}

/*
 * Current count of black stones.
 */
int Board::countBlack() {
    return black.count();
}

/*
 * Current count of white stones.
 */
int Board::countWhite() {
    return taken.count() - black.count();
}

/*
 * Sets the board state given an 8x8 char array where 'w' indicates a white
 * piece and 'b' indicates a black piece. Mainly for testing purposes.
 */
void Board::setBoard(char data[]) {
    taken.reset();
    black.reset();
    for (int i = 0; i < 64; i++) {
        if (data[i] == 'b') {
            taken.set(i);
            black.set(i);
        } if (data[i] == 'w') {
            taken.set(i);
        }
    }
}

// will usually return a positive number (depends on bonus). 
// will not return a negative number for the other side.
// includes bonus/multipolier. 
int Board::score(Move *m, Side side){
    int X = m->getX();
    int Y = m->getY();
    int x = X;
    int y = Y;
    int score = 1;
    int count = 0;

    // left
    while(onBoard(X - 1, Y) && occupied(X - 1, Y))
    {
        // if piece is the other color
        if(!get(side, X - 1, Y))
        {
            X--;
            count++;
        }
        // other color enclosed in this color
        else
        {
            score += count;
            break;
        }
    }
    count = 0;
    X = x;

    // right
    if(onBoard(X + 1, Y) && occupied(X + 1, Y))
    {
        // if piece is the other color
        if(!get(side, X + 1, Y))
        {
            X++;
            count++;
        }
        // other color enclosed in this color
        else
        {
            score += count;
            break;
        }
    }
    count = 0;
    X = x;

    // above
    if(onBoard(X, Y + 1) && occupied(X, Y + 1))
    {
        // if piece is the other color
        if(!get(side, X, Y + 1))
        {
            Y++;
            count++;
        }
        // other color enclosed in this color
        else
        {
            score += count;
            break;
        }
    }
    count = 0;
    Y = y;

    // below 
    if(onBoard(X, Y - 1) && occupied(X, Y - 1))
    {
        // if piece is the other color
        if(!get(side, X, Y - 1))
        {
            Y--;
            count++;
        }
        // other color enclosed in this color
        else
        {
            score += count;
            break;
        }
    }
    count = 0;
    Y = y;

    // top left
    if(onBoard(X - 1, Y + 1) && occupied(X - 1, Y + 1))
    {
        // if piece is the other color
        if(!get(side, X - 1, Y + 1))
        {
            X--;
            Y++
            count++;
        }
        // other color enclosed in this color
        else
        {
            score += count;
            break;
        }
    }
    count = 0;
    X = x;
    Y = y;

    // bottom left
    if(onBoard(X - 1, Y - 1) && occupied(X - 1, Y - 1))
    {
        // if piece is the other color
        if(!get(side, X - 1, Y - 1))
        {
            X--;
            Y--;
            count++;
        }
        // other color enclosed in this color
        else
        {
            score += count;
            break;
        }
    }
    count = 0;
    X = x;
    Y = y;

    // top right
    if(onBoard(X + 1, Y + 1) && occupied(X + 1, Y + 1))
    {
        // if piece is the other color
        if(!get(side, X + 1, Y + 1))
        {
            X++;
            Y++;
            count++;
        }
        // other color enclosed in this color
        else
        {
            score += count;
            break;
        }
    }
    count = 0;
    X = x;
    Y = y;

    // bottom right
    if(onBoard(X + 1, Y - 1) && occupied(X + 1, Y - 1))
    {
        // if piece is the other color
        if(!get(side, X + 1, Y - 1))
        {
            X++;
            Y--;
            count++;
        }
        // other color enclosed in this color
        else
        {
            score += count;
            break;
        }
    }
    count = 0;
    X = x;
    Y = y;

    // adds bonuses depending on position of board

    if ((X == 1 && (Y == 1 || Y == 6)) || (X == 6 && (Y == 1 || Y == 6)))
    {
       score -= 3;
    }

    else if ((X == 0 && (Y == 0 || Y == 7)) || (X == 7 && (Y == 7 || Y == 0)))
    {
        score += 3;
    }
    else if ((X == 0 && (Y == 1 || Y == 6)) || (X == 1 && (Y == 0 || Y == 7)) || (X == 6 && (Y == 0 || Y == 7)) || (X == 7 && (Y == 1 || Y == 6)))
    {
        score -= 2;
    }
    else if (X == 0 || X == 7 || Y == 0 || Y == 7)
    {
        score += 2;
    }

    return score;
}

