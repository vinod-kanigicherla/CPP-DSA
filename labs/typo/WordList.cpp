#include "WordList.h"
#include "Heap.h"

#include <cmath>
#include <map>

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
  std::map<char, std::pair<float, float>> locations = {
      {'q', {0.0, 0.0}}, {'w', {1.0, 0.0}}, {'e', {2.0, 0.0}},
      {'r', {3.0, 0.0}}, {'t', {4.0, 0.0}}, {'y', {5.0, 0.0}},
      {'u', {6.0, 0.0}}, {'i', {7.0, 0.0}}, {'o', {8.0, 0.0}},
      {'p', {9.0, 0.0}}, {'a', {0.5, 1.0}}, {'s', {1.5, 1.0}},
      {'d', {2.5, 1.0}}, {'f', {3.5, 1.0}}, {'g', {4.5, 1.0}},
      {'h', {5.5, 1.0}}, {'j', {6.5, 1.0}}, {'k', {7.5, 1.0}},
      {'l', {8.5, 1.0}}, {'z', {1.0, 2.0}}, {'x', {2.0, 2.0}},
      {'c', {3.0, 2.0}}, {'v', {4.0, 2.0}}, {'b', {5.0, 2.0}},
      {'n', {6.0, 2.0}}, {'m', {7.0, 2.0}}};

  Heap heap(maxcount);

  for (const std::string &word : mWords) {
    float score = 0;
    for (size_t i = 0; i < points.size(); i++) {
      std::pair<float, float> key_location = locations[word[i]];
      float distance = sqrt(pow(key_location.first - points[i].x, 2) +
                            pow(key_location.second - points[i].y, 2));
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
