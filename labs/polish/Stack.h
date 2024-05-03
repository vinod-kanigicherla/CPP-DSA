#ifndef STACK_H
#define STACK_H

#include "AST.h"
#include <string>

// Use this file to define your Stack type.
// Implement its member functions in Stack.cpp.

class Stack {
  size_t nCount;
  size_t nCapacity;
  AST** nodes;

 public:
  Stack(): nCount(0), nCapacity(2), nodes(new AST*[nCapacity]) {};
  ~Stack();

  size_t count() const;
  void push(AST* node);
  AST* pop();
};

#endif
