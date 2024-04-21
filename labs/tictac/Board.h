#ifndef BOARD_H
#define BOARD_H

#include "Move.h"

// I recommended writing a Board class to manage your game state.
// Here's some space for the class definition; member functions go in Board.cpp.

#include <vector>
#include <string>

using namespace std;

class Board {

private:
    vector< vector<char> > grid;
    int move_num;
    char prev_player;

public:
    Board();

    bool isValid(int row, int col) const;
    bool put(int row, int col, char player);
    string checkWin() const;
    string getStatus() const;
};

#endif // BOARD_H

