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

std::string NumberNode::prefix() const {
    return format(num);
}

std::string NumberNode::postfix() const {
    return format(num); 
}

double NumberNode::value() const {
    return num; 
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
                throw std::runtime_error("Division by zero.");
            return left->value() / right->value();
        case '%':
            lval = left->value();
            rval = right->value();
            if (rval == 0) 
                throw std::runtime_error("Division by zero.");
            return std::fmod(lval, rval);
        case '~':
            return -1 * value();
        default:
            throw std::runtime_error("Unsupported operator: " + std::string(1, op));
    }
}

NegationNode::~NegationNode() {
    delete operand;
}

std::string NegationNode::prefix() const {
    return "~ " + operand->prefix();
}

std::string NegationNode::postfix() const {
    return operand->postfix() + " ~";
}

double NegationNode::value() const {
    return -1 * operand->value();
}

