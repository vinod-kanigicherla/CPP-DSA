#include "Board.h"
#include "Errors.h"
#include "Move.h"
#include <iostream>
#include <sstream>

using namespace std;
int main() {
    Board board;
    string line;
    int move_number = 1;

    while (getline(cin, line)) {
        istringstream iss(line);
        int num;
        char player;
        char rowChar;
        int col;
        if (!(iss >> num >> player >> rowChar >> col) || num != move_number) {
            cout << "Parse error.";
            return 1;
        }

        int row = rowChar - 'A';
        col -= 1; 

        if (!board.put(row, col, player)) {
            cout << "Invalid move.";
            return 2;
        }

        string turn_result = board.checkWin();

        if (!turn_result.empty()) {
            cout << turn_result << std::endl;
            return 0;
        }

        move_number++;
    }

    cout << board.getStatus() << std::endl;
    return 0;
}
