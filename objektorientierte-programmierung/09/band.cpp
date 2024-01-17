#include "band.h"
#include <stdexcept>
#include <vector>

Band::Band(const std::string &name, const int &founded, const Song &mostPopular)
    : Band(name, founded, mostPopular, nullptr, 0){};

Band::Band(const std::string &name, const int &founded, const Song &mostPopular,
           std::string *members, const int size)
    : name(name), founded(founded), mostPopular(mostPopular),
      members(std::vector<std::string>(members, members + size)) {}

const bool Band::operator==(const Band &other) const {
  if (other.getSize() != members.size() || other.getName() != name ||
      other.getFounded() != founded || other.getMostPopular() != mostPopular) {
    return false;
  }

  for (int i = 0; i < other.getSize(); i++) {
    if (other.getMember(i) != members[i]) {
      return false;
    }
  }

  return true;
};

const bool Band::operator!=(const Band &other) const {
  return !((*this) == other);
};

void Band::checkIndex(int i) const {
  if (members.size() == 0) {
    throw std::invalid_argument("Size is zero. There is nothing to set or get");
  } else if (i < 0) {
    throw std::invalid_argument("index can't be negative");
  } else if (i >= members.size()) {
    throw std::invalid_argument("index can't be bigger than size");
  }
};

const std::string &Band::getName() const { return name; }

const int &Band::getFounded() const { return founded; }

const Song &Band::getMostPopular() const { return mostPopular; }

const int Band::getSize() const { return members.size(); }

const std::string &Band::getMember(const int i) const {
  checkIndex(i);

  return members[i];
}

void Band::setMember(int i, const std::string &name) {
  checkIndex(i);

  members[i] = name;
}

void Band::addMember(const std::string &name) { members.push_back(name); }

int Band::compare(const Band &other) const {
  return other.getFounded() - founded;
};
