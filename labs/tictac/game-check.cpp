#include "Board.h"
#include "Errors.h"
#include "Move.h"
#include <iostream>

using namespace std;
int main() {
    Board board;
    string line;
    int move_number = 1;

    try {
        while (getline(cin, line)) {
            Move move(line);  

            int row = move.row - 1;
            int col = move.column - 1;
            char player = move.player;

            try {
                board.put(row, col, player);
            } catch (const ParseError& e) {
                cout << "Invalid move." << endl;
                return 2;
            }

            string turn_result = board.checkWin();
            if (!turn_result.empty()) {
                cout << turn_result << '\n';
                return 0;
            }

            move_number++;
        }
        cout << board.getStatus() << '\n';
    } catch (const ParseError& e) {
        cout << "Parse error." << '\n';
        return 1;
    }
    return 0;
}
