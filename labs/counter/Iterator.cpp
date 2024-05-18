#include "Counter.h"

// Counter::Iterator Member Functions

const std::string &Counter::Iterator::key() const { return counterNode->key; }

int Counter::Iterator::value() const { return counterNode->value; }

void Counter::Iterator::operator++() {
  if (counterNode) {
    counterNode = counterNode->next;
  }
}

bool Counter::Iterator::operator==(const Iterator &other) const {
  return counterNode == other.counterNode;
}

bool Counter::Iterator::operator!=(const Iterator &other) const {
  return counterNode != other.counterNode;
}
