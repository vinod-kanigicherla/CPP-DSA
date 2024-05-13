#ifndef PERSON_H
#define PERSON_H

#include "Enums.h"

#include <set>
#include <string>
// This is the Person class you need to implement.
// It has many member functions that perform relationship queries.
// Add any member variables you need to support this.
// Implement the member functions in Person.cpp.

class Person {
  // Member Variables
  // Add _ for avoiding naming conflicts
  std::string name_;
  Gender gender_;
  Person *mother_;
  Person *father_;
  std::set<Person *> children_;

  // Helper Functions

public:
  Person(const std::string &name, Gender gender, Person *mother = nullptr,
         Person *father = nullptr)
      : name_(name), gender_(gender), mother_(mother), father_(father) {
    if (mother) {
      mother->addChild(this);
    }
    if (father) {
      father->addChild(this);
    }
  }

  ~Person() {};

  const std::string &name() const;
  Gender gender() const;
  Person *mother();
  Person *father();
  std::set<Person *> children() const;

  // Required Relationship Functions
  std::set<Person *> ancestors(PMod pmod = PMod::ANY);
  std::set<Person *> aunts(PMod pmod = PMod::ANY, SMod smod = SMod::ANY);
  std::set<Person *> brothers(PMod pmod = PMod::ANY, SMod smod = SMod::ANY);
  std::set<Person *> children() { return children_; }
  std::set<Person *> cousins(PMod pmod = PMod::ANY, SMod smod = SMod::ANY);
  std::set<Person *> daughters();
  std::set<Person *> descendants();
  std::set<Person *> grandchildren();
  std::set<Person *> granddaughters();
  std::set<Person *> grandfathers(PMod pmod = PMod::ANY);
  std::set<Person *> grandmothers(PMod pmod = PMod::ANY);
  std::set<Person *> grandparents(PMod pmod = PMod::ANY);
  std::set<Person *> grandsons();
  std::set<Person *> nephews(PMod pmod = PMod::ANY, SMod smod = SMod::ANY);
  std::set<Person *> nieces(PMod pmod = PMod::ANY, SMod smod = SMod::ANY);
  std::set<Person *> parents(PMod pmod = PMod::ANY);
  std::set<Person *> siblings(PMod pmod = PMod::ANY, SMod smod = SMod::ANY);
  std::set<Person *> sisters(PMod pmod = PMod::ANY, SMod smod = SMod::ANY);
  std::set<Person *> sons();
  std::set<Person *> uncles(PMod pmod = PMod::ANY, SMod smod = SMod::ANY);

  // Other Member Functions
  void setMother(Person *mother) { mother_ = mother; }
  void setFather(Person *father) { father_ = father; }
  void addChild(Person *child) { children_.insert(child); }
};
#endif
