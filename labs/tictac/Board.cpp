#include "Errors.h"
#include "Board.h"

// Space for implementing Board functions.

#include <iostream>
#include <vector>
using namespace std;


Board::Board() {
  this->grid = vector< vector<char> >(3, vector<char>(3, '.'));
  this->move_num = 0;
  this->prev_player = ' ';
}

bool Board::isValid(int row, int col) const {
    return (row >= 0 && row < 3) && (col >= 0 && col < 3) && grid[row][col] == '.';
}

bool Board::put(int row, int col, char player) {
    if (prev_player == player) {
        throw ParseError("Players need to alternate turns");
    }
    if (!isValid(row, col)) {
        throw ParseError("Spot already taken or out of bounds");
    }
    grid[row][col] = player;
    prev_player = player;
    move_num++;
    return true;
}

string Board::checkWin() const {
    for (int i = 0; i < 3; i++) {
        if (grid[i][0] != '.' && grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2]) {
            return "Game over: " + string(1, grid[i][0]) + " wins.";
        }
        if (grid[0][i] != '.' && grid[0][i] == grid[1][i] && grid[1][i] == grid[2][i]) {
            return "Game over: " + string(1, grid[0][i]) + " wins.";
        }
    }

    if (grid[0][0] != '.' && grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2]) {
        return "Game over: " + string(1, grid[0][0]) + " wins.";
    }
    if (grid[0][2] != '.' && grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0]) {
        return "Game over: " + string(1, grid[0][2]) + " wins.";
    }

    if (move_num == 9) {
        return "Game over: Draw.";
    }

    return "";
}
string Board::getStatus() const {
    // if (checkWin() == "") {
    //     throw ParseError("Game Over");
    // }
    // if (move_num == 9) {
    //     throw ParseError("Game over: Draw. No further moves allowed");
    // }

    if (move_num == 0) return "Game in progress: New game.";
    char next_player = (prev_player == 'X' ? 'O' : 'X');
    return "Game in progress: " + string(1, next_player) + "'s turn.";
}
