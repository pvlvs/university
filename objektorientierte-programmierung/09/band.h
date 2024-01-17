#ifndef band_h
#define band_h

#include "song.h"
#include <vector>

class Band {
  std::string name;
  int founded;
  Song mostPopular;
  std::vector<std::string> members;

  void checkIndex(int i) const;

public:
  Band(const std::string &name, const int &founded, const Song &mostPopular);

  Band(const std::string &name, const int &founded, const Song &mostPopular,
       std::string *members, const int size);

  const bool operator==(const Band &other) const;

  const bool operator!=(const Band &other) const;

  const std::string &getName() const;

  const int &getFounded() const;

  const Song &getMostPopular() const;

  const int getSize() const;

  const std::string &getMember(const int i) const;

  void setMember(int i, const std::string &name);

  void addMember(const std::string &name);

  int compare(const Band &other) const;
};

#endif
