#include "GenePool.h"
#include "Person.h"
#include <map>
#include <sstream>

GenePool::GenePool(std::istream &stream) {
  std::string line;
  while (std::getline(stream, line)) {
    if (line.empty() || line[0] == '#')
      continue;

    std::istringstream iss(line);
    std::string name, gender_str, mother_str, father_str;

    std::getline(iss, name, '\t');
    std::getline(iss, gender_str, '\t');
    std::getline(iss, mother_str, '\t');
    std::getline(iss, father_str, '\t');

    Gender gender = (gender_str == "male") ? Gender::MALE : Gender::FEMALE;

    Person *mother =
        (mother_str != "???" && people.find(mother_str) != people.end())
            ? people[mother_str]
            : nullptr;
    Person *father =
        (father_str != "???" && people.find(father_str) != people.end())
            ? people[father_str]
            : nullptr;

    Person *person = new Person(name, gender, mother, father);
    people[name] = person;
  }
}

GenePool::~GenePool() {
  for (auto &item : people) {
    delete item.second;
  }
}

std::set<Person *> GenePool::everyone() const {
  std::set<Person *> all_people;
  for (const auto &item : people) {
    all_people.insert(item.second);
  }
  return all_people;
}

Person *GenePool::find(const std::string &name) const {
  auto it = people.find(name);
  return it != people.end() ? it->second : nullptr;
}
