#ifndef band_h
#define band_h

#include "song.h"
#include <string>

class Band {
  std::string name;
  int founded;
  Song mostPopular;

public:
  Band(const std::string &name, const int &founded, const Song &mostPopular);

  const std::string &getName() const;

  const int &getFounded() const;

  const Song &getMostPopular() const;

  int compare(const Band &other) const;
};

#endif
