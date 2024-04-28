#ifndef NODE_H
#define NODE_H

using namespace std;

#include <string>

struct Node {
  // TODO!
  string value;
  Node* left;
  Node* right;
  Node* parent;
  size_t weight;

  Node(string value);
};

#endif
