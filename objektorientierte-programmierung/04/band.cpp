#include "band.h"
#include "song.h"

Band::Band(const std::string &name, const int &founded, const Song &mostPopular)
    : name(name), founded(founded), mostPopular(mostPopular){};

const std::string &Band::getName() const { return name; }

const int &Band::getFounded() const { return founded; }

const Song &Band::getMostPopular() const { return mostPopular; }

int Band::compare(const Band &other) const {
  return other.getFounded() - founded;
};
