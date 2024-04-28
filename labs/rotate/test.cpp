#include "Tree.h"
#include <iostream>
#include <string>

// This file is for you to test your tree functions.
// It won't be graded - do whatever you want.

int main() {
  Tree tree;

  // Do tree things!
  std::string node = "a";
  std::string node1 = "b";
  std::string node2 = "c";
  tree.insert(node);
  tree.insert(node1);
  tree.insert(node2);
  tree.remove(2);
  tree.print();
  std::cout << tree.contains("a");
  std::cout << tree.find("a");
  std::cout << tree.count();
  std::cout << tree.lookup(0);
  tree.clear();
  tree.print();

  return 0;
}
