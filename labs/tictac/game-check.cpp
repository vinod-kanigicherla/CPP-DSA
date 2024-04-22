#include "Board.h"
#include "Errors.h"
#include "Move.h"
#include <iostream>

int main() {
    Board board;
    string line;
    int move_number = 1;

    try {
        string turn_result;
        while (getline(cin, line)) {
            Move move(line);

            if (board.isGameOver()) {
                cout << "Invalid move. Game over.\n";
                return 2; 
            }

            if (move.number != move_number) {
                cout << "Invalid move sequence.\n";
                return 2;
            }

            try {
                board.put(move.row - 1, move.column - 1, move.player);
            } catch (const ParseError& e) {
                cout << "Invalid move: " << e.what() << '\n';
                return 2;
            }

            turn_result = board.checkWin();
            // if (!turn_result.empty()) {
            //     cout << turn_result << '\n';
            //     board.setGameOver();
            // }

            move_number++;
        }

        if (!turn_result.empty()) {
            cout << turn_result << '\n';
            board.setGameOver();
        } else {
            cout << board.getStatus() << '\n';

        }
    } catch (const ParseError& e) {
        cout << "Parse error: " << e.what() << '\n';
        return 1;
    }
    return 0;  
}
