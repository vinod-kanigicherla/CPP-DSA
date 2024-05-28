#include "WordList.h"
#include "Heap.h"
#include "Point.h"

#include <cmath>

bool validWord(const std::string &word) {
  for (char c : word) {
    if (!std::islower(c)) {
      return false;
    }
  }
  return true;
}

WordList::WordList(std::istream &stream) {
  std::string word;
  while (getline(stream, word)) {
    if (validWord(word)) {
      mWords.push_back(word);
    }
  }
}

Heap WordList::correct(const std::vector<Point> &points, size_t maxcount,
                       float cutoff) const {
  Heap heap(maxcount);

  for (const std::string &word : mWords) {
    float score = 0;
    for (size_t i = 0; i < points.size(); i++) {
      int char_index = word[i] - 'a';
      float distance = sqrt(pow(QWERTY[char_index].x - points[i].x, 2) +
                            pow(QWERTY[char_index].y - points[i].y, 2));
      score += (1.0 / (10 * pow(distance, 2) + 1));
    }

    if (score < cutoff)
      continue;
    if (heap.count() < heap.capacity()) {
      heap.push(word, score);
    } else if (score > heap.top().score) {
      heap.pushpop(word, score);
    }
  }

  return heap;
}
