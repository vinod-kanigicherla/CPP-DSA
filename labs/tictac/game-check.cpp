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

    try {
        while (getline(cin, line)) {
            Move move(line);
            istringstream iss(line);
            int num;
            char player;
            char rowChar;
            int col;
            if (!(iss >> num >> player >> rowChar >> col) || num != move_number) {
                throw ParseError("Parse error.");
            }
            
            if (num != move_number || (player != 'X' && player != 'O')) {
                throw ParseError("Parse error."); 
            }


            int row = rowChar - 'A';
            col -= 1; 

            if (!board.put(row, col, player)) {
                throw ParseError("Parse error."); 
            }

            string turn_result = board.checkWin();
            if (!turn_result.empty()) {
                cout << turn_result << '\n';
                return 0;
            }

            move_number++;
        }
        cout << board.getStatus() << '\n';
        return 0;
    } catch (const ParseError& e) {
        cout << "Parse error." << '\n';
        return 1;
    }
}
