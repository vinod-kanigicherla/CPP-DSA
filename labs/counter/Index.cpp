#include "Index.h"

// Index Member Functions

Index::Index() {
  table = new Bucket[capacity];
  for (int i = 0; i < capacity; ++i) {
    table[i] = Bucket();
  }
}

Index::~Index() { delete[] table; }

// Best Hash Function Found: DJB2
int Index::hash(const std::string &key) const {
  unsigned long hash_value = 5381;
  for (char c : key) {
    hash_value = ((hash_value << 5) + hash_value) + c;
  }
  return hash_value % capacity;
}

// Linear Probe
int Index::probe(int idx, const std::string &key) const {
  int start = idx;
  while (table[idx].filled && table[idx].key != key) {
    idx = (idx + 1) % capacity;
    if (idx == start)
      return -1;
  }
  return idx;
}

void Index::insert(const std::string &key, Node *node) {
  if (size >= capacity)
    return;
  int idx = hash(key);
  idx = probe(idx, key);
  if (idx == -1)
    return;
  table[idx].key = key;
  table[idx].node = node;
  table[idx].filled = true;
  size++;
}

void Index::remove(const std::string &key) {
  int idx = hash(key);
  idx = probe(idx, key);
  if (idx != -1 && table[idx].filled) {
    table[idx].filled = false;
    size--;
  }
}

Node *Index::find(const std::string &key) const {
  int idx = hash(key);
  idx = probe(idx, key);
  if (idx != -1 && table[idx].filled) {
    return table[idx].node;
  }
  return nullptr;
}
