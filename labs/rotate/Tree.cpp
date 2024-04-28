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

size_t Tree::findHelper(const Node* node, const std::string& s) const {
  size_t index = 0;

  while (node) {
    size_t left_size = (node->left) ? node->left->weight: 0; 
    if (s == node->value) {
      return index + left_size;
    } else if (s < node->value) {
      node = node->left;
    } else {
      index += left_size + 1;
      node = node->right;
    }
  }

  return std::numeric_limits<size_t>::max();
}

size_t Tree::find(const std::string& s) const {
  return findHelper(root, s);
}

void Tree::insertHelper(Node*& node, const std::string& s) {
  if (node == nullptr) {
    node = new Node(s);
    return;
  }

  if (s < node->value) {
    insertHelper(node->left, s);
  } else {
    insertHelper(node->right, s);
  }

  updateWeights(node);
  rotate(node);
}

void Tree::insert(const std::string& s){
  insertHelper(root, s);
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

    updateWeights(node);
    int leftWeight = node->left ? node->left->weight : 0;
    int rightWeight = node->right ? node->right->weight : 0;
    int currentImbalance = std::abs(leftWeight - rightWeight);

    if (currentImbalance <= 1) return;

    if (leftWeight > rightWeight) {
        if (node->left && node->left->right && node->left->left &&
            node->left->right->weight > node->left->left->weight) {
            int newImbalance = std::abs(static_cast<int>(node->left->weight - (node->left->left ? node->left->left->weight : 0)));
            if (newImbalance < currentImbalance) {
                leftRotate(node->left);
            }
        }
        int predictedImbalance = std::abs(static_cast<int>((node->left ? node->left->weight : 0) - node->weight));
        if (predictedImbalance < currentImbalance) {
            rightRotate(node);
        }
    } else {
        if (node->right && node->right->left && node->right->right &&
            node->right->left->weight > node->right->right->weight) {
            int newImbalance = std::abs(static_cast<int>(node->right->weight - (node->right->right ? node->right->right->weight : 0)));
            if (newImbalance < currentImbalance) {
                rightRotate(node->right);
            }
        }
        int predictedImbalance = std::abs(static_cast<int>(node->weight - (node->right ? node->right->weight : 0)));
        if (predictedImbalance < currentImbalance) {
            leftRotate(node);
        }
    }
}

void Tree::rightRotate(Node*& root) {
    Node* leftChild = root->left;
    if (!leftChild) return;

    root->left = leftChild->right;
    leftChild->right = root;
    root = leftChild;

    updateWeights(root->right);
    updateWeights(root);     
}



void Tree::leftRotate(Node*& root) {
    Node* rightChild = root->right;
    if (!rightChild) return;

    root->right = rightChild->left;
    rightChild->left = root;
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

