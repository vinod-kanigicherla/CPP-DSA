#ifndef TREE_H
#define TREE_H

#include "Node.h"

class Tree {
  // Member Variables
  Node* root;
  // Private Helper Functions
  void clearHelper(Node* node);
  bool containsHelper(const Node* node, const std::string& s) const;
  size_t findHelper(const Node* node, const std::string& s, size_t& index) const;
  void insertHelper(Node*& node, const std::string& s, Node* parent);
  std::string lookupHelper(const Node* node, size_t index, size_t currIndex) const;
  std::string printHelper(const Node* node) const;
  std::string findMinValue(Node* node); 
  Node* removeHelper(Node*& node, size_t index, size_t currIndex);
  void rotate(Node*& node);
  int getImbalance(Node* node);
  void rightRotate(Node*& node);
  void leftRotate(Node*& node);
  void updateWeights(Node* node);

public:
  Tree();
  ~Tree();

  // Public Member Functions
  void        clear();
  size_t      count() const;
  bool        contains(const std::string& s) const;
  size_t      find(const std::string& s) const;
  void        insert(const std::string& s);
  std::string lookup(size_t index) const;
  void        print() const;
  void        remove(size_t index);
};

#endif
