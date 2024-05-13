#include "Person.h"
#include "Enums.h"

// Person Member Functions

const std::string &Person::name() const { return name_; }
Gender Person::gender() const { return gender_; }
Person *Person::mother() const { return mother_; }
Person *Person::father() const { return father_; }
std::set<Person *> Person::children() const { return children_; }

std::set<Person *> Person::ancestors(PMod pmod) {
  std::set<Person *> res = parents(pmod);
  std::set<Person *> next;
  for (Person *parent : res) {
    std::set<Person *> parentAncestors = parent->ancestors(pmod);
    next.insert(parentAncestors.begin(), parentAncestors.end());
  }
  res.insert(next.begin(), next.end());
  return res;
}

std::set<Person *> Person::aunts(PMod pmod, SMod smod) {
  std::set<Person *> res;
  if (pmod == PMod::MATERNAL || pmod == PMod::ANY) {
    if (mother_) {
      for (Person *sib : mother_->siblings(PMod::ANY, smod)) {
        if (sib->gender() == Gender::FEMALE) {
          res.insert(sib);
        }
      }
    }
  }
  if (pmod == PMod::PATERNAL || pmod == PMod::ANY) {
    if (father_) {
      for (Person *sib : father_->siblings(PMod::ANY, smod)) {
        if (sib->gender() == Gender::FEMALE) {
          res.insert(sib);
        }
      }
    }
  }
  return res;
}

std::set<Person *> Person::brothers(PMod pmod, SMod smod) {
  std::set<Person *> res;
  std::set<Person *> sibs = siblings(pmod, smod);
  for (Person *sib : sibs) {
    if (sib->gender() == Gender::MALE) {
      res.insert(sib);
    }
  }
  return res;
}

std::set<Person *> Person::cousins(PMod pmod, SMod smod) {
  std::set<Person *> result;
  std::set<Person *> auntsAndUncles;

  std::set<Person *> auntsSet = aunts(pmod, smod);
  std::set<Person *> unclesSet = uncles(pmod, smod);

  auntsAndUncles.insert(auntsSet.begin(), auntsSet.end());
  auntsAndUncles.insert(unclesSet.begin(), unclesSet.end());

  for (Person *relative : auntsAndUncles) {
    std::set<Person *> relativeChildren = relative->children();
    result.insert(relativeChildren.begin(), relativeChildren.end());
  }

  return result;
}
std::set<Person *> Person::daughters() {
  std::set<Person *> res;
  for (Person *child : children_) {
    if (child->gender() == Gender::FEMALE) {
      res.insert(child);
    }
  }
  return res;
}

std::set<Person *> Person::descendants() {
  std::set<Person *> res;
  for (Person *child : children_) {
    res.insert(child);
    std::set<Person *> childDescendants = child->descendants();
    res.insert(childDescendants.begin(), childDescendants.end());
  }
  return res;
}

std::set<Person *> Person::grandchildren() {
  std::set<Person *> res;
  for (Person *child : children_) {
    for (Person *grandchild : child->children()) {
      res.insert(grandchild);
    }
  }
  return res;
}
std::set<Person *> Person::granddaughters() {
  std::set<Person *> res;
  for (Person *grandchild : grandchildren()) {
    if (grandchild->gender() == Gender::FEMALE) {
      res.insert(grandchild);
    }
  }
  return res;
}

std::set<Person *> Person::grandfathers(PMod pmod) {
  std::set<Person *> res;
  for (Person *grandparent : grandparents(pmod)) {
    if (grandparent->gender() == Gender::MALE) {
      res.insert(grandparent);
    }
  }
  return res;
}
std::set<Person *> Person::grandmothers(PMod pmod) {
  std::set<Person *> res;
  for (Person *grandparent : grandparents(pmod)) {
    if (grandparent->gender() == Gender::FEMALE) {
      res.insert(grandparent);
    }
  }
  return res;
}

std::set<Person *> Person::grandparents(PMod pmod) {
  std::set<Person *> res;
  if (pmod == PMod::MATERNAL || pmod == PMod::ANY) {
    if (mother_) {
      if (mother_->mother()) {
        res.insert(mother_->mother());
      }
      if (mother_->father()) {
        res.insert(father_->father());
      }
    }
  }

  if (pmod == PMod::PATERNAL || pmod == PMod::ANY) {
    if (father_) {
      if (father_->father()) {
        res.insert(father_->father());
      }
      if (mother_->father()) {
        res.insert(mother_->father());
      }
    }
  }

  return res;
}

std::set<Person *> Person::grandsons() {
  std::set<Person *> res;
  for (Person *grandchild : grandchildren()) {
    if (grandchild->gender() == Gender::MALE) {
      res.insert(grandchild);
    }
  }
  return res;
}

std::set<Person *> Person::nieces(PMod pmod, SMod smod) {
  std::set<Person *> res;
  for (Person *sibling : siblings(pmod, smod)) {
    for (Person *possNiece : sibling->children()) {
      if (possNiece->gender() == Gender::FEMALE) {
        res.insert(possNiece);
      }
    }
  }
  return res;
}

std::set<Person *> Person::nephews(PMod pmod, SMod smod) {
  std::set<Person *> res;
  for (Person *sibling : siblings(pmod, smod)) {
    for (Person *possNiece : sibling->children()) {
      if (possNiece->gender() == Gender::MALE) {
        res.insert(possNiece);
      }
    }
  }
  return res;
}

std::set<Person *> Person::parents(PMod pmod) {
  std::set<Person *> res;
  if (pmod == PMod::MATERNAL) {
    if (mother_) {
      res.insert(mother_);
    }
  } else if (pmod == PMod::PATERNAL) {
    if (father_) {
      res.insert(father_);
    }
  } else if (pmod == PMod::ANY) {
    if (mother_) {
      res.insert(mother_);
    }
    if (father_) {
      res.insert(father_);
    }
  }
  return res;
}

std::set<Person *> Person::siblings(PMod pmod, SMod smod) {
  std::set<Person *> res;
  if ((pmod == PMod::MATERNAL || pmod == PMod::ANY) && mother_) {
    for (Person *child : mother_->children()) {
      if (child != this &&
          (smod == SMod::ANY ||
           (smod == SMod::FULL && father_ && (child->father() == father_)))) {
        res.insert(child);
      } else if (child != this && smod == SMod::HALF &&
                 (!father_ || child->father() != father_)) {
        res.insert(child);
      }
    }
  }
  if ((pmod == PMod::PATERNAL || pmod == PMod::ANY) && father_) {
    for (Person *child : father_->children()) {
      if (child != this && res.find(child) == res.end() &&
          (smod == SMod::ANY ||
           (smod == SMod::FULL && mother_ && (child->mother() == mother_)))) {
        res.insert(child);
      } else if (child != this && smod == SMod::HALF &&
                 (!mother_ || child->mother() != mother_)) {
        res.insert(child);
      }
    }
  }
  return res;
}

std::set<Person *> Person::sisters(PMod pmod, SMod smod) {
  std::set<Person *> res;
  std::set<Person *> sibs = siblings(pmod, smod);
  for (Person *sib : sibs) {
    if (sib->gender() == Gender::FEMALE) {
      res.insert(sib);
    }
  }
  return res;
}

std::set<Person *> Person::sons() {
  std::set<Person *> res;
  for (Person *child : children_) {
    if (child->gender() == Gender::MALE) {
      res.insert(child);
    }
  }
  return res;
}

std::set<Person *> Person::uncles(PMod pmod, SMod smod) {
  std::set<Person *> res;
  if (pmod == PMod::MATERNAL || pmod == PMod::ANY) {
    if (mother_) {
      for (Person *sib : mother_->siblings(PMod::ANY, smod)) {
        if (sib->gender() == Gender::MALE) {
          res.insert(sib);
        }
      }
    }
  }
  if (pmod == PMod::PATERNAL || pmod == PMod::ANY) {
    if (father_) {
      for (Person *sib : father_->siblings(PMod::ANY, smod)) {
        if (sib->gender() == Gender::MALE) {
          res.insert(sib);
        }
      }
    }
  }
  return res;
}
