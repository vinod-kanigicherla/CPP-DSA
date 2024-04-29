#include "Tree.h"
#include "Node.h"
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
// Tree Function Implementations

Tree::Tree() {
  this->root = nullptr;
}


void Tree::clearHelper(Node* node) {
  if (node == nullptr) return;

  clearHelper(node->left);
  clearHelper(node->right);

  delete node;
}

Tree::~Tree() {
  clear();
}

void Tree::clear() {
  clearHelper(root);
  root = nullptr;
}

size_t Tree::count() const{
  if (root == nullptr) {
    return 0;
  }
  return root->weight;
}

bool Tree::containsHelper(const Node* node, const std::string& s) const {
  if (node == nullptr) {
    return false;
  }
  if (node->value == s) {
    return true;
  }

  if (s < node->value) {
    return containsHelper(node->left, s);
  } else {
    return containsHelper(node->right, s);
  }

}

bool Tree::contains(const std::string& s) const {
  return containsHelper(root, s);
}


size_t Tree::findHelper(const Node* node, const std::string& s, size_t& index) const {
    if (node == nullptr) {
        return std::numeric_limits<size_t>::max();
    }

    if (s < node->value) {
        return findHelper(node->left, s, index);
    } else if (s > node->value) {
        index += (node->left ? node->left->weight : 0) + 1;
        return findHelper(node->right, s, index);
    } else {
        size_t left_result = findHelper(node->left, s, index);
        return left_result == std::numeric_limits<size_t>::max() ? index : left_result;
    }
}

size_t Tree::find(const std::string& s) const {
    size_t index = 0;
    return findHelper(root, s, index);
}


void Tree::insertHelper(Node*& node, const std::string& s, Node* parent) {
    if (!node) {
        node = new Node(s);
        node->parent = parent; 
    } else if (s <= node->value) {
        insertHelper(node->left, s, node); 
    } else {
        insertHelper(node->right, s, node);
    }
    updateWeights(node);
    rotate(node);
}

void Tree::insert(const std::string& s){
  insertHelper(root, s, nullptr);
}


std::string Tree::printHelper(const Node* node) const {
    if (node == nullptr) {
        return "-";  
    }

    std::string left = (node->left ? printHelper(node->left) : "-");
    std::string right = (node->right ? printHelper(node->right) : "-");

    if (left == "-" && right == "-") {
        return node->value; 
    }

    return "(" + left + " " + node->value + " " + right + ")";
}

void Tree::print() const {
  std::cout << printHelper(root) << "\n";
}

std::string Tree::lookupHelper(const Node* node, size_t index, size_t currIndex) const {
    if (node == nullptr) {
        throw std::out_of_range("Index out of range");
    }

    size_t leftWeight = node->left ? node->left->weight : 0;
    size_t rightIndex = currIndex + leftWeight;  

    if (index == rightIndex) {
        return node->value;
    } else if (index < rightIndex) {
        return lookupHelper(node->left, index, currIndex);  
    } else {
        return lookupHelper(node->right, index, rightIndex + 1);
    }
}

std::string Tree::lookup(size_t index) const { 
  return lookupHelper(root, index, 0); 
} 

std::string Tree::findMinValue(Node* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node->value;
}


Node* Tree::removeHelper(Node*& node, size_t index, size_t currIndex) {
    if (node == nullptr) {
        throw std::out_of_range("Index out of range");
    }

    size_t leftWeight = node->left ? node->left->weight : 0;
    size_t nodeIndex = currIndex + leftWeight;

    if (index == nodeIndex) {
        if (node->left && node->right) {
            node->value = findMinValue(node->right);
            removeHelper(node->right, 0, nodeIndex + 1);
        } else {
            Node* temp = (node->left != nullptr) ? node->left : node->right;
            delete node;
            node = temp; 
        }
    } else if (index < nodeIndex) {
        node->left = removeHelper(node->left, index, currIndex);
    } else {
        node->right = removeHelper(node->right, index, nodeIndex + 1);
    }

    if (node) {
        updateWeights(node); 
        rotate(node); 
  }
    return node;
}

void Tree::remove(size_t index) {
  removeHelper(root, index, 0);
}

void Tree::rotate(Node*& node) {
    if (node == nullptr) return;

    int leftWeight = node->left ? node->left->weight : 0;
    int rightWeight = node->right ? node->right->weight : 0;
    int currentImbalance = std::abs(static_cast<int>(leftWeight - rightWeight));

    if (currentImbalance == 0) return;

    if (leftWeight > rightWeight && node->left && node->left->right) {
        int leftRightWeight = node->left->right->weight;
        int leftLeftWeight = node->left->left ? node->left->left->weight : 0;

        if (leftRightWeight > leftLeftWeight) {
            leftRotate(node->left); 
        }
        updateWeights(node);
        int newBalanceAfterLR = std::abs(static_cast<int>((node->left ? node->left->weight : 0) - node->weight));
        if (newBalanceAfterLR < currentImbalance) {
            rightRotate(node);
        }
    }
    else if (rightWeight > leftWeight && node->right && node->right->left) {
        int rightLeftWeight = node->right->left->weight;
        int rightRightWeight = node->right->right ? node->right->right->weight : 0;

        if (rightLeftWeight > rightRightWeight) {
            rightRotate(node->right);
        }
        updateWeights(node);
        int newBalanceAfterRL = std::abs(static_cast<int>(node->weight - (node->right ? node->right->weight : 0)));
        if (newBalanceAfterRL < currentImbalance) {
            leftRotate(node); 
        }
    }
    else if (leftWeight > rightWeight) {
        rightRotate(node);
    }
    else if (rightWeight > leftWeight) {
        leftRotate(node);
    }
}



void Tree::rightRotate(Node*& root) {
    Node* leftChild = root->left;
    if (!leftChild) return;

    root->left = leftChild->right;
    if (leftChild->right != nullptr) {
        leftChild->right->parent = root; 
    }

    leftChild->parent = root->parent;
    leftChild->right = root;
    root->parent = leftChild;

    root = leftChild;
    updateWeights(root->right);
    updateWeights(root);
}


void Tree::leftRotate(Node*& root) {
    Node* rightChild = root->right;
    if (!rightChild) return;

    root->right = rightChild->left;
    if (rightChild->left != nullptr) {
        rightChild->left->parent = root; 
    }

    rightChild->parent = root->parent;
    rightChild->left = root;
    root->parent = rightChild;

    root = rightChild;    
    updateWeights(root->left);
    updateWeights(root);
}

void Tree::updateWeights(Node* node) {
    if (node) {
        int leftWeight = node->left ? node->left->weight : 0;
        int rightWeight = node->right ? node->right->weight : 0;
        node->weight = leftWeight + rightWeight + 1; 
    }
}

