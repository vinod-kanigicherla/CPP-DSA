#include "AST.h"
#include "Nodes.h"
#include "Stack.h"

#include <sstream>
#include <stdexcept>
#include <string>

AST* AST::parse(const std::string &expression) {
    std::string token;
    std::istringstream stream(expression);
    Stack* stack = new Stack();

    while (stream >> token) {
        if (token.size() == 1 && std::string("+-*/%").find(token) != std::string::npos) {
            if (stack->count() < 2)
                throw std::runtime_error("Not enough operands");
            AST* right = stack->pop();
            AST* left = stack->pop();
            stack->push(new OperatorNode(token[0], left, right));
        } else {
            try {
                double num = std::stod(token);
                stack->push(new NumberNode(num));
            } catch (const std::invalid_argument& ex) {
                delete &stack;
                throw std::runtime_error("Invalid token: " + token);
            }
        }
    }

    if (stack->count() == 0) {
        throw std::runtime_error("No input");
    }
    if (stack->count() > 1) {
        throw std::runtime_error("Too many operands");
    }

    return stack->pop();
}

