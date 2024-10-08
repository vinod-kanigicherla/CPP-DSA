#include "Move.h"
#include <cctype>
#include <string>
#include <vector>
#include <cstdlib>
#include "Errors.h"
using namespace std;

Move::Move(const string& input) {
    vector<string> move_tokens;
    string curr_word;

    size_t comment_index = input.find('#');
    if (comment_index != string::npos) {
        if (comment_index > 0 && (!isspace(input[comment_index - 1]))) {
            throw ParseError("Comment must be preceded by whitespace");
        }
    }

    if (!input.empty() && isspace(input.front()) && (comment_index == string::npos || comment_index > 0)) {
        throw ParseError("Leading whitespace not allowed.");
    }

    for (char c : input) {
        if (c == '#') {
            break;
        }
    
        if (isspace(c)) {
            if (!curr_word.empty()) {
                move_tokens.push_back(curr_word);
                curr_word.clear();
            }
        } else {
            curr_word += c;
        }
    }

    if (!curr_word.empty()) {
        move_tokens.push_back(curr_word);
    }

    if (move_tokens.size() != 3) throw ParseError("Incomplete move information.");

    string moveNumberStr = move_tokens[0];
    if (moveNumberStr.length() != 1 || !isdigit(moveNumberStr[0])) {
        throw ParseError("Invalid number.");
    }

    this->number = moveNumberStr[0] - '0';
    if (this->number < 1 || this->number > 9) {
        throw ParseError("Move number should be between 1 and 9.");
    }

    this->player = toupper(move_tokens[1][0]);
    this->row = toupper(move_tokens[2][0]) - 'A' + 1;
    this->column = move_tokens[2][1] - '0';

    if (this->player != 'X' && this->player != 'O') {
        throw ParseError("Player must be X or O");
    }
    if (this->row < 1 || this->row > 3 || this->column < 1 || this->column > 3) {
        throw ParseError("Row or column out of valid range.");
    }
}

string Move::to_string() const {
    return std::to_string(this->number) + " " + string(1, this->player) + " " + string(1, static_cast<char>(this->row - 1 + 'A')) + std::to_string(this->column);
}
