#include "band.h"
#include "iostream"
#include <functional>
#include <stdexcept>

Band::Band(const std::string &name, const int &founded, const Song &mostPopular)
    : Band(name, founded, mostPopular, new std::string[0], 0){};

Band::Band(const std::string &name, const int &founded, const Song &mostPopular,
           std::string *members, const uint size)
    : name(name), founded(founded), mostPopular(mostPopular),
      members(makeMembers(members, size)), size(size){};

std::string *Band::makeMembers(std::string *members, const uint &size) {
  if (members == nullptr) {
    throw std::invalid_argument("members cannot be null");
  }

  std::string *ret = new std::string[size];

  for (int i = 0; i < size; i++) {
    ret[i] = members[i];
  }

  return ret;
}

const std::string &Band::getName() const { return name; }

const int &Band::getFounded() const { return founded; }

const Song &Band::getMostPopular() const { return mostPopular; }

const uint &Band::getSize() const { return size; }

const std::string &Band::getMember(const uint i) const {
  if (i >= size) {
    throw std::invalid_argument("i is to big");
  }

  return members[i];
}

int Band::compare(const Band &other) const {
  return other.getFounded() - founded;
};
