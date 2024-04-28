#include "Node.h"

// Node Function Implementations

Node::Node(string value) {
  this->value = value;
  this->left = nullptr;
  this->right = nullptr;
  this->weight = 1;
}
