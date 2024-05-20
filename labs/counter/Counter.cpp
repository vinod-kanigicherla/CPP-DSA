#include "Counter.h"

// Counter Member Functions

Counter::Counter() : keys_count(0), total_count(0) {}
Counter::~Counter() {}

size_t Counter::count() const { return keys_count; }

int Counter::total() const { return total_count; }

void Counter::inc(const std::string &key, int by) {
  Node *node = index.find(key);

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
  Node *node = index.find(key);

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
  Node *node = index.find(key);
  if (node != nullptr) {
    index.remove(key);
    total_count -= node->value;
    keys_count--;
    counter.remove(node);
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
  Node *node = index.find(key);

  if (node != nullptr) {
    total_count += count - node->value;
    node->value = count;
  } else {
    counter.append(key, count);
    index.insert(key, counter.tail);
    keys_count++;
    total_count += count;
  }
}
