#include "Nodes.h"

#include <sstream>
#include <stdexcept>
#include <string> 
#include <cmath>
// This creates the number format the autograder expects:
std::string format(double number) {
  std::ostringstream stream;
  stream << number;
  return stream.str();
}

std::string OperatorNode::prefix() const {
  return std::string(1, op) + " " + left->prefix() + " " + right->prefix();
}

std::string OperatorNode::postfix() const {
  return left->postfix() + " " + right->postfix() + " " + std::string(1, op);
}

double OperatorNode::value() const {
    double lval = 0;
    double rval = 0;

    switch (op) {
        case '+': 
            return left->value() + right->value();
        case '-': 
            return left->value() - right->value();
        case '*': 
            return left->value() * right->value();
        case '/':
            if (right->value() == 0) 
                throw std::runtime_error("Division by zero");
            return left->value() / right->value();
        case '%':
            lval = left->value();
            rval = right->value();
            if (rval == 0) 
                throw std::runtime_error("Division by zero");
            return std::fmod(lval, rval);
        default:
            throw std::runtime_error("Unsupported operator: " + std::string(1, op));
    }
}


