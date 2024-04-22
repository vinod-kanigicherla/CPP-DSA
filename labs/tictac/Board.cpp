#include "Errors.h"
#include "Board.h"

// Space for implementing Board functions.

#include <vector>
using namespace std;


Board::Board() {
  this->grid = vector< vector<char> >(3, vector<char>(3, '.'));
  this->move_num = 0;
  this->prev_player = ' ';
  this->game_over = false;  
}

bool Board::isValid(int row, int col) const {
    return !game_over && (row >= 0 && row < 3) && (col >= 0 && col < 3) && grid[row][col] == '.';
}

bool Board::put(int row, int col, char player) {
    if (game_over) {
        throw ParseError("No further moves. Game over.");
    }
    if (prev_player == player) {
        throw ParseError("Players need to alternate turns");
    }
    if (!isValid(row, col)) {
        throw ParseError("Spot already taken or out of bounds");
    }
    grid[row][col] = player;
    prev_player = player;
    move_num++;
    setGameOver();
    return true;
}

void Board::setGameOver() {
    if (!checkWin().empty() || move_num == 9) {
        game_over = true;
    }
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
    
    // if (game_over) {
    //     string result = checkWin();
    //     if (!result.empty()) {
    //         return result;  
    //     }
    //     return "Game over: Draw."; 
    // }

    if (move_num == 0) return "Game in progress: New game.";
    char next_player = (prev_player == 'X' ? 'O' : 'X');
    return "Game in progress: " + string(1, next_player) + "'s turn.";
}
