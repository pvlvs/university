#include "band.h"
#include "iostream"

Band::Band(const Band &other)
    : Band(other.name, other.founded, other.mostPopular, other.members,
           other.size) {}

Band::~Band() { delete[] members; }

Band::Band(const std::string &name, const int &founded, const Song &mostPopular)
    : Band(name, founded, mostPopular, nullptr, 0){};

Band::Band(const std::string &name, const int &founded, const Song &mostPopular,
           std::string *members, const uint size)
    : name(name), founded(founded), mostPopular(mostPopular),
      members(makeMembers(members, size)), size(size) {}

Band &Band::operator=(const Band &other) {
  if (this == &other) {
    return *this;
  }

  name = other.getName();
  founded = other.getFounded();
  mostPopular = other.getMostPopular();
  size = other.getSize();

  if (other.size > 0) {
    delete[] members;
    members = new std::string[size];

    for (int i = 0; i < other.size; i++) {
      members[i] = other.getMember(i);
    }
  }

  return *this;
};

const bool Band::operator==(const Band &other) const {
  if (other.getSize() != size || other.getName() != name ||
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

std::string *Band::makeMembers(std::string *members, const uint &size) {
  if (members == nullptr && size != 0) {
    throw std::invalid_argument("members cannot be null with a positive size");
  } else if (size < 0) {
    throw std::invalid_argument("size can't be negative");
  }

  if (members == nullptr) {
    return nullptr;
  }

  std::string *ret = new std::string[size];

  for (int i = 0; i < size; i++) {
    ret[i] = members[i];
  }

  return ret;
}

void Band::checkIndex(int i) const {
  if (size == 0) {
    throw std::invalid_argument("Size is zero. There is nothing to set or get");
  } else if (i < 0) {
    throw std::invalid_argument("index can't be negative");
  } else if (i >= size) {
    throw std::invalid_argument("index can't be bigger than size");
  }
};

const std::string &Band::getName() const { return name; }

const int &Band::getFounded() const { return founded; }

const Song &Band::getMostPopular() const { return mostPopular; }

const uint &Band::getSize() const { return size; }

const std::string &Band::getMember(const uint i) const {
  checkIndex(i);

  return members[i];
}

void Band::setMember(int i, const std::string &name) {
  checkIndex(i);

  members[i] = name;
}

void Band::addMember(const std::string &name) {
  size++;
  std::string *membersCopy = makeMembers(members, size);
  delete[] members;

  members = membersCopy;
  delete[] membersCopy;

  setMember(size - 1, name);
}

int Band::compare(const Band &other) const {
  return other.getFounded() - founded;
};
