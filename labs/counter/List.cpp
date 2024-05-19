#include "List.h"

// List Member Functions

Node::~Node() {}

List::~List() {
  Node *curr = head;
  while (curr != nullptr) {
    Node *next = curr->next;
    delete curr;
    curr = next;
  }
  head = nullptr;
  tail = nullptr;
}

void List::append(const std::string &key, int value) {
  Node *node = new Node(key, value);
  if (tail == nullptr) {
    head = tail = node;
  } else {
    tail->next = node;
    node->prev = node;
    tail = tail->next;
  }
}

Node *List::find(const std::string &key) const {
  Node *findNode = head;
  while (findNode != nullptr) {
    if (findNode->key == key) {
      return findNode;
    }
    findNode = findNode->next;
  }
  return nullptr;
}

void List::remove(Node *node) {
  if (node == nullptr)
    return;

  if (node->prev) {
    node->prev->next = node->next;
  } else {
    head = node->next;
    if (head)
      head->prev = nullptr;
  }

  if (node->next) {
    node->next->prev = node->prev;
  } else {
    tail = node->prev;
    if (tail)
      tail->next = nullptr;
  }

  delete node;
}
