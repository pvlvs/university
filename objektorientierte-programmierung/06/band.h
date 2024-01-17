#ifndef band_h
#define band_h

#include "song.h"

class Band {
  std::string name;
  int founded;
  Song mostPopular;
  std::string *members;
  uint size;

  std::string *makeMembers(std::string *members, const uint &size);

  void checkIndex(int i) const;

public:
  Band(const Band &other);

  ~Band();

  Band(const std::string &name, const int &founded, const Song &mostPopular);

  Band(const std::string &name, const int &founded, const Song &mostPopular,
       std::string *members, const uint size);

  const std::string &getName() const;

  const int &getFounded() const;

  const Song &getMostPopular() const;

  const uint &getSize() const;

  const std::string &getMember(const uint i) const;

  std::string *getMembers();

  void setMember(int i, const std::string &name);

  int compare(const Band &other) const;
};

#endif
