#include "Errors.h"
#include "Move.h"

#include <iostream>

using namespace std;

int main(int argc, char** argv) {
  bool verbose = false;
  int prev_num = 0;

  if(argc == 2 && string(argv[1]) == "-v") {
    verbose = true;
  }

  if(verbose) {
    cout << "> ";
  }

  string line;
  getline(cin, line);

  try {
    Move move(line);
    if (move.number != prev_num + 1) {
      throw ParseError("Invalid format: Not consecutive move number");
    }
    prev_num = move.number;

    cout << move.to_string() << '\n';
    return 0;
  }
  catch(const ParseError& e) {
    if(verbose) {
      cout << "Parse error: " << e.what() << '\n';
    }
    else {
      cout << "Parse error.\n";
    }
    return 1;
  }
}
