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


void Tree::insertHelper(Node*& node, const std::string& s, Node* parent, bool moveLeft) {
    if (!node) {
        node = new Node(s);
        node->parent = parent;
    } else if (s <= node->value) {
        insertHelper(node->left, s, node, true);
    } else {
        insertHelper(node->right, s, node, false);
    }
    updateWeights(node);
    rotate(node, moveLeft);
}

void Tree::insert(const std::string& s) {
  insertHelper(root, s, nullptr, false);
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

Node* Tree::removeHelper(Node*& node, size_t index, size_t currIndex, bool isLeftSubtree) {
    if (!node) {
        throw std::out_of_range("Index out of range");
    }

    size_t leftWeight = node->left ? node->left->weight : 0;
    size_t nodeIndex = currIndex + leftWeight;

    if (index == nodeIndex) {
        if (node->left && node->right) {
            Node* parentOfMin = node;
            Node* minNode = node->right;
            while (minNode->left) {
                parentOfMin = minNode;
                minNode = minNode->left;
            }
            node->value = minNode->value;
            if (parentOfMin == node) {
                parentOfMin->right = minNode->right;
                if (minNode->right) {
                    minNode->right->parent = parentOfMin;
                }
            } else {
                parentOfMin->left = minNode->right;
                if (minNode->right) {
                    minNode->right->parent = parentOfMin;
                }
            }
            delete minNode;

            // Update weights from the parent of the minimum node to the actual node
            Node* temp = parentOfMin;
            while (temp) {
                updateWeights(temp);
                temp = temp->parent;
            }
        } else {
            Node* temp = node->left ? node->left : node->right;
            delete node;
            node = temp;
        }
    } else if (index < nodeIndex) {
        node->left = removeHelper(node->left, index, currIndex, true);
    } else {
        node->right = removeHelper(node->right, index, nodeIndex + 1, false);
    }

    if (node) {
        updateWeights(node);
        rotate(node, isLeftSubtree);
    }
    return node;
}




void Tree::remove(size_t index) {
    removeHelper(root, index, 0, false);
}


int Tree::getImbalance(Node* node) {
    if (node == nullptr) return 0;
    int leftWeight = node->left ? node->left->weight : 0;
    int rightWeight = node->right ? node->right->weight : 0;
    return std::abs(leftWeight - rightWeight);
}

// Example refined function to check improvements post-rotation
int predictImbalanceAfterRightRotation(Node* node) {
    if (!node || !node->left) return std::numeric_limits<int>::max();
    
    // Nodes that will be directly affected by the rotation
    Node* leftChild = node->left;
    Node* leftChildsRight = leftChild ? leftChild->right : nullptr;

    // Calculate potential new weights after the rotation
    int newLeftWeight = leftChild->left ? leftChild->left->weight : 0;
    int newRightWeight = node->right ? node->right->weight : 0;
    if (leftChildsRight) newRightWeight += leftChildsRight->weight;
    newRightWeight += 1; // Adding the current node as part of the new right subtree

    return std::abs(newLeftWeight - newRightWeight);
}



int predictImbalanceAfterLeftRotation(Node* node) {
    if (!node || !node->right) return std::numeric_limits<int>::max();

    // Nodes that will be directly affected by the rotation
    Node* rightChild = node->right;
    Node* rightChildsLeft = rightChild ? rightChild->left : nullptr;

    // Calculate potential new weights after the rotation
    int newRightWeight = rightChild->right ? rightChild->right->weight : 0;
    int newLeftWeight = node->left ? node->left->weight : 0;
    if (rightChildsLeft) newLeftWeight += rightChildsLeft->weight;
    newLeftWeight += 1; // Adding the current node as part of the new left subtree

    return std::abs(newLeftWeight - newRightWeight);
}



void Tree::rotate(Node*& node, bool moveLeft) {
    if (node == nullptr) return;

    updateWeights(node);
    int leftWeight = node->left ? node->left->weight : 0;
    int rightWeight = node->right ? node->right->weight : 0;
    int currentImbalance = std::abs(leftWeight - rightWeight);


    Node* originalRoot = node; 

    if (leftWeight > rightWeight) {
        rightRotate(node);
        updateWeights(node);
        int newImbalance = std::abs(static_cast<int>((node->left ? node->left->weight : 0) - (node->right ? node->right->weight : 0)));

        if (newImbalance >= currentImbalance) {
            leftRotate(node);
            node = originalRoot;
            updateWeights(node);
        }
    } else if (rightWeight > leftWeight) {
        leftRotate(node);
        updateWeights(node); 
        int newImbalance = std::abs(static_cast<int>((node->left ? node->left->weight : 0) - (node->right ? node->right->weight : 0)));

        if (newImbalance >= currentImbalance) {
            rightRotate(node);
            node = originalRoot;
            updateWeights(node);
        }
    }

    updateWeights(node);
}


void Tree::rightRotate(Node*& root) {
    if (!root || !root->left) return;
    Node* leftChild = root->left;
    root->left = leftChild->right;
    if (leftChild->right) {
        leftChild->right->parent = root;
    }
    leftChild->right = root;
    Node* oldParent = root->parent;
    root->parent = leftChild;
    leftChild->parent = oldParent;
    if (oldParent) {
        if (oldParent->left == root) oldParent->left = leftChild;
        else oldParent->right = leftChild;
    }
    root = leftChild;
    updateWeights(root->right);
    updateWeights(root);
}

void Tree::leftRotate(Node*& root) {
    if (!root || !root->right) return;
    Node* rightChild = root->right;
    root->right = rightChild->left;
    if (rightChild->left) {
        rightChild->left->parent = root;
    }
    rightChild->left = root;
    Node* oldParent = root->parent;
    root->parent = rightChild;
    rightChild->parent = oldParent;
    if (oldParent) {
        if (oldParent->left == root) oldParent->left = rightChild;
        else oldParent->right = rightChild;
    }
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

