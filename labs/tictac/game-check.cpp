#include "Board.h"
#include "Errors.h"
#include "Move.h"
#include <iostream>

using namespace std;

int main() {
    Board board;
    string line;
    int move_number = 1;
    string turn_result; 

    try {
        while (getline(cin, line)) {
            Move move(line);

            if (move.number != move_number) {
                cout << "Invalid move.\n";
                return 2;
            }

            if (board.isGameOver()) {
                cout << "Invalid move.\n";
                return 2; 
            }

            try {
                board.put(move.row - 1, move.column - 1, move.player);
            } catch (const ParseError& e) {
                cout << "Invalid move.\n";
                return 2;
            }

            turn_result = board.checkWin();
            if (!turn_result.empty()) {
                board.setGameOver(); 
            }

            move_number++;
        }

        if (!turn_result.empty()) {
            cout << turn_result << '\n';
        } else {
            cout << board.getStatus() << '\n';
        }
    } catch (const ParseError& e) {
        cout << "Parse error." << '\n';
        return 1; 
    }
    return 0;
} 
