#include "Stack.h"
#include <algorithm>
#include <stdexcept>

// Implement your Stack member functions here.

Stack::~Stack() {
  for (size_t i = 0; i < nCount; i++) {
    delete nodes[i];
  }
  delete [] nodes;
}

size_t Stack::count() const {
  return nCount;
}

void Stack::push(AST* node) {
  if (nCount >= nCapacity) {
    AST** newNodes = new AST*[nCapacity * 2];
    std::copy(nodes, nodes + nCount, newNodes);
    delete [] nodes;
    nodes = newNodes;
    nCapacity *= 2;
  }

  nodes[nCount++] = node;
}

AST* Stack::pop() {
  // Possibly add stack underflow here
  return nodes[--nCount];
}
