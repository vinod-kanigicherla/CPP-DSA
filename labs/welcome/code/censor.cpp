#include <iostream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

int main(int argc, char** argv) {

	if (argc != 2) {
		cout << "USAGE: censor [length]";
		return 1;
	}

	size_t length = atoi(argv[1]);

	string line;
	getline(cin, line);

	vector<string> words;
	string curr_word;
	
	for (char c: line) {
		if (isspace(c)) {
			if(!curr_word.empty()) {
				if (curr_word.length() != length) words.push_back(curr_word);
				curr_word.clear();
			}
		} else {
			curr_word += c;
		}
	}
	
	if (!curr_word.empty() && curr_word.length() != length) words.push_back(curr_word);

	for (size_t i = 0; i < words.size(); i++) {
		if (i == words.size() - 1) {
			cout << words[i];
	        } else {
			cout << words[i] << " ";
		}
	}

	return 0;
}
