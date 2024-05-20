#ifndef INDEX_H
#define INDEX_H

#include "List.h"
#include <string>

// TODO...
struct Bucket {
  Node *node;
  bool filled;
  std::string key;

  Bucket() : node(nullptr), filled(false), key("") {}
};

class Index {
  Bucket *table;
  int capacity = 100003; // Large Prime!
  int size = 0;

  int hash(const std::string &key) const;
  int doubleHash(const std::string &key) const;
  int probe(int idx, const std::string &key) const;

public:
  Index();
  ~Index();

  void insert(const std::string &key, Node *node);
  void remove(const std::string &key);
  Node *find(const std::string &key) const;
};

#endif
