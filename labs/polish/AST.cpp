#include "AST.h"
#include "Nodes.h"
#include "Stack.h"

#include <sstream>
#include <stdexcept>
#include <string>

#include <cctype>

bool checkInvalidToken(const std::string& token) {
    size_t start = 0; 
    if (token[0] == '+' || token[0] == '-') {
        if (token.size() == 1) return true;
        start = 1;
    }

    bool seen = false;
    for (size_t i = start; i < token.length(); i++) {
        if (token[i] == '.') {
            if (seen) return true;
            seen = true;
        } else if (!std::isdigit(token[i])) {
            return true;
        }
    }

    return false;
}


AST* AST::parse(const std::string &expression) {
    std::string token;
    std::istringstream stream(expression);
    Stack* stack = new Stack();

    while (stream >> token) {
        if (token.size() == 1 && std::string("+-*/%~").find(token) != std::string::npos) {
            if (token[0] == '~') {
                if (stack->count() < 1) {
                    delete stack;
                    throw std::runtime_error("Not enough operands.");
                }
                AST* operand = stack->pop();
                stack->push(new NegationNode(operand));
            } else {
                if (stack->count() < 2) {
                    delete stack;
                    throw std::runtime_error("Not enough operands.");
                }
                AST* right = stack->pop();
                AST* left = stack->pop();
                stack->push(new OperatorNode(token[0], left, right));
            }
        }  else {
            if (checkInvalidToken(token)) {
                delete stack;
                throw std::runtime_error("Invalid token: " + token);
            } else {
                double num = std::stod(token);
                stack->push(new NumberNode(num));
            }
        }
    }

    if (stack->count() == 0) {
        delete stack;
        throw std::runtime_error("No input.");
    }
    if (stack->count() > 1) {
        delete stack;
        throw std::runtime_error("Too many operands.");
    }

    AST* result = stack->pop();
    delete stack;
    return result;
}

