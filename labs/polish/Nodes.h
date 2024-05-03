#ifndef NODES_H
#define NODES_H

#include "AST.h"
#include <string>

class NumberNode : public AST {
    double num;

public:
    NumberNode(double num) : num(num) {}
    virtual ~NumberNode() {}

    virtual std::string prefix() const override { return std::to_string(num); }
    virtual std::string postfix() const override { return std::to_string(num); }
    virtual double value() const override { return num; }
};

class OperatorNode : public AST {
    char op;
    AST* left;
    AST* right;

public:
    OperatorNode(char op, AST* left, AST* right) : op(op), left(left), right(right) {}
    virtual ~OperatorNode() {
        delete left;
        delete right;
    }

    virtual std::string prefix() const override;
    virtual std::string postfix() const override;
    virtual double value() const override;
};

// Special Node: Negation (Single-Child!)

class NegationNode : public AST {
    AST* operand; 

 public:
    NegationNode(AST* operand) : operand(operand) {}
    virtual ~NegationNode();

    virtual std::string prefix() const override; 
    virtual std::string postfix() const override;
    virtual double value() const override;
};
#endif // NODES_H
