#include <iostream>
#include <list>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
using namespace std;

// store row, col of a point on the screen
class coord {
public:
    int row, col;
};


// a square has a position on the screen and what 
// character to display there.
class square {
public:
    coord where;
    char what;
};


// base class for blocks.  there will be specialized
// versions for each of the different shapes.
class block {
public:
    int row, col; // position of left-upper corner of the block
    list<square> squares; // squares the block is made of

    // constructor - shape is a doubly-NULL terminated string, where
    // each row of the block is terminated by a single NULL character.
    block(char* shape, int gameWidth) {
        // by default start in the top middle of the screen
        row = 0;
        col = gameWidth / 2;

        // scan through the shape to pull squares
        // out of it.
        int r = 0, c = 0;
        bool lastWasNull = false;
        square sq;
        for (int i = 0; ; i++) {
            if (shape[i] == '\0') {
                if (lastWasNull) break; // two NULL's in a row, we're done.
                else {
                    // one NULL - go to the next row.
                    lastWasNull = true;
                    r++; c = 0;
                    continue;
                }
            }
            lastWasNull = false; // not a NULL

            // if not a space, put a new square for this in our list of squares
            if (shape[i] != ' ') {
                sq.where.row = r; sq.where.col = c;
                sq.what = shape[i];
                squares.push_back(sq);
            }
            c++; // move over one column.
        }
    }

    // display the block on the screen, or erase it from the screen.
    // note: displayBlock(win); is the same as displayBlock(win, true);
    void displayBlock(WINDOW* win, bool yes = true) {
        // go through list of blocks and draw each one.
        for (list<square>::iterator it = squares.begin(); it != squares.end(); ++it) {
            if (yes)
                mvwprintw(win, row + it->where.row, col + it->where.col, "%c", it->what);
            else
                mvwprintw(win, row + it->where.row, col + it->where.col, " ");
        }
    }

    // move block down 
    void moveDown(WINDOW* win) {
        // first draw blanks where I was before.
        displayBlock(win, false);
        row++;
        // now redraw where I am now.
        displayBlock(win, true);
    }

    // move block to the left
    void moveLeft(WINDOW* win) {
        // first draw blanks where I was before.
        displayBlock(win, false);
        col--;
        // now redraw where I am now.
        displayBlock(win, true);
    }

    // move block to the right
    void moveRight(WINDOW* win) {
        // first draw blanks where I was before.
        displayBlock(win, false);
        col++;
        // now redraw where I am now.
        displayBlock(win, true);
    }

};


// the specialized block classes.  each one
// calls the block constructor with a different 
// shape.  otherwise, they're all the same and just
// use the inherited methods and variables from block.

class blockT : public block {
public:
    blockT(int gameWidth) :
        block((char*)
            " t \0"
            "ttt\0", gameWidth) {
    }
};

class block_ : public block {
public:
    block_(int gameWidth) :
        block((char*)
            "====\0", gameWidth) {
    }
};

class blockL : public block {
public:
    blockL(int gameWidth) :
        block((char*)
            "l  \0"
            "lll\0", gameWidth) {
    }
};

class block7 : public block {
public:
    block7(int gameWidth) :
        block((char*)
            "  7\0"
            "777\0", gameWidth) {
    }
};

class block2 : public block {
public:
    block2(int gameWidth) :
        block((char*)
            " 22\0"
            "22 \0", gameWidth) {
    }
};

class blockZ : public block {
public:
    blockZ(int gameWidth) :
        block((char*)
            "zz \0"
            " zz\0", gameWidth) {
    }
};

class block0 : public block {
public:
    block0(int gameWidth) :
        block((char*)
            "00\0"
            "00\0", gameWidth) {
    }
};


// function to create a new random block and 
// return a pointer to it.  gameWidth is needed
// for the block constructor so it knows where
// the middle of the screen is.  which is which
// one to create, which typically is rand()%7
block* newBlock(int which, int gameWidth) {
    which = which % 7; // must be 0 - 6 because there are only 7 kinds of blocks
    switch (which) {
    case 0: return new block0(gameWidth);
    case 1: return new blockZ(gameWidth);
    case 2: return new block2(gameWidth);
    case 3: return new block7(gameWidth);
    case 4: return new blockL(gameWidth);
    case 5: return new block_(gameWidth);
    case 6: return new blockT(gameWidth);
    default: return new blockT(gameWidth);
    }
}

// signal handler for SIGALRM, defined below.
void alarmFunc(int signal);

class refactored {
public:
    list<block*> blocks; // list of blocks
    bool timeToMoveDown; // flag set in signal handler when time to move block down.
    int gameWidth, gameHeight;
    // constructor - save the width and height for the game.
    void Init(int width, int height) {
        gameWidth = width;
        gameHeight = height;
        timeToMoveDown = false;
    }

    void playGame() {

    }

    // can the given block be moved by the given change in row and column?
    bool canMove(block* b, int deltaR, int deltaC) {
        // for each square of the b block...
        for (list<square>::iterator it = b->squares.begin();
            it != b->squares.end(); ++it) {
            // new location for that square
            int newR = b->row + it->where.row + deltaR,
                newC = b->col + it->where.col + deltaC;

            // would it go off the screen?
            if (newC < 1 || newC > gameWidth ||
                newR < 0 || newR >= gameHeight) return false;

            // would it collide with any other blocks?
            for (list<block*>::iterator itt = blocks.begin();
                itt != blocks.end(); ++itt) {
                block* otherB = *itt;
                if (otherB == b) continue; // don't check if I'll collide with myself

                for (list<square>::iterator it2 = otherB->squares.begin();
                    it2 != otherB->squares.end(); ++it2) {
                    if (otherB->row + it2->where.row == newR &&
                        otherB->col + it2->where.col == newC) return false;
                }
            }
        }
        return true;
    }

    bool canDown(block* b) {
        return canMove(b, 1, 0);
    }

    bool canRight(block* b) {
        return canMove(b, 0, 1);
    }

    bool canLeft(block* b) {
        return canMove(b, 0, -1);
    }

};
