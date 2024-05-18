#ifndef LIST_H
#define LIST_H

#include <string>

class Node {
public:
  std::string key;
  int value;
  Node *prev;
  Node *next;

  Node(const std::string &key, int value, Node *prev = nullptr,
       Node *next = nullptr)
      : key(key), value(value), prev(prev), next(next) {}
  ~Node();
};

class List {
public:
  Node *head;
  Node *tail;

  List() : head(nullptr), tail(nullptr) {}
  ~List();

  void append(const std::string &key, int value);
  Node *find(const std::string &key) const;
  void remove(Node *node);
};

#endif
