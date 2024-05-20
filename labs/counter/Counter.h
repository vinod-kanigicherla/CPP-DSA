#ifndef COUNTER_H
#define COUNTER_H

#include "Index.h"
#include "List.h"
#include <cstddef>
#include <string>

// This is the Counter class you need to implement.
// It includes the Counter::Iterator as a nested class.

class Counter {
public:
  class Iterator {
    // Member Variables
    Node *counterNode;

  public:
    Iterator(Node *node = nullptr) : counterNode(node) {}

    const std::string &key() const;
    int value() const;

    void operator++();
    bool operator==(const Iterator &other) const;
    bool operator!=(const Iterator &other) const;
  };

private:
  // Member Variables
  List counter;
  Index index;
  int keys_count;
  int total_count;

private:
  // Helper Functions

public:
  Counter();
  ~Counter();

  size_t count() const;
  int total() const;

  void inc(const std::string &key, int by = 1);
  void dec(const std::string &key, int by = 1);
  void del(const std::string &key);
  int get(const std::string &key) const;
  void set(const std::string &key, int count);

  Iterator begin() const { return Iterator(counter.head); }
  Iterator end() const { return Iterator(nullptr); }
};

#endif
