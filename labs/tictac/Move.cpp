#include "Move.h"
#include <iostream>
#include <cctype>
#include <string>
#include <vector>
#include <cstdlib> // For atoi and c_str

using namespace std;

// Implementing the constructor to parse input string into move components.
Move::Move(const string& input) {
    vector<string> move_tokens;
    string curr_word;

    for (char c : input) {
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

    this->number = atoi(move_tokens[0].c_str());
    this->player = toupper(move_tokens[1][0]);
    this->row = toupper(move_tokens[2][0]) - 'A' + 1;
    this->column = move_tokens[2][1] - '0';
}

string Move::to_string() const {
    return std::to_string(this->number) + " " + string(1, this->player) + " " + string(1, static_cast<char>(this->row - 1 + 'A')) + std::to_string(this->column);
}
