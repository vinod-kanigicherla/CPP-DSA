#include "Counter.h"

// Counter Member Functions

Counter::Counter() {}
Counter::~Counter() {}

size_t Counter::count() const {
  size_t count = 0;
  Node *curr = counter.head;
  while (curr != nullptr) {
    count++;
    curr = curr->next;
  }
  return count;
}

int Counter::total() const {
  int total = 0;
  Node *curr = counter.head;
  while (curr != nullptr) {
    total += curr->value;
    curr = curr->next;
  }
  return total;
}

void Counter::inc(const std::string &key, int by) {
  Node *node = counter.find(key);

  if (node != nullptr) {
    node->value += by;
  } else {
    counter.append(key, by);
  }
}

void Counter::dec(const std::string &key, int by) {
  Node *node = counter.find(key);

  if (node != nullptr) {
    node->value -= by;
  } else {
    counter.append(key, -by); // <= CHECK HERE
  }
}

void Counter::del(const std::string &key) {
  Node *node = counter.find(key);
  if (node)
    counter.remove(node);
}

int Counter::get(const std::string &key) const {
  Node *node = counter.find(key);
  if (node) {
    return node->value;
  }
  return 0;
}

void Counter::set(const std::string &key, int count) {
  Node *node = counter.find(key);

  if (node != nullptr) {
    node->value = count;
  } else {
    counter.append(key, count);
  }
}
