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
    total_count += by;
  } else {
    counter.append(key, by);
    index.insert(key, counter.tail);
    total_count += by;
    keys_count++;
  }
}

void Counter::dec(const std::string &key, int by) {
  Node *node = counter.find(key);

  if (node != nullptr) {
    node->value -= by;
    total_count -= by;
  } else {
    counter.append(key, -by); // <= CHECK HERE
    index.insert(key, counter.tail);
    keys_count++;
    total_count -= by;
  }
}

void Counter::del(const std::string &key) {
  Node *node = counter.find(key);
  if (node != nullptr) {
    index.remove(key);
    counter.remove(node);
    keys_count--;
    total_count -= node->value;
  }
}

int Counter::get(const std::string &key) const {
  Node *node = index.find(key);
  if (node) {
    return node->value;
  }
  return 0;
}

void Counter::set(const std::string &key, int count) {
  Node *node = counter.find(key);

  if (node != nullptr) {
    node->value = count;
    total_count += count - node->value;
  } else {
    counter.append(key, count);
    index.insert(key, counter.tail);
    keys_count++;
    total_count += count;
  }
}
