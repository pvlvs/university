#ifndef song_h
#define song_h

#include <string>

class Song {
  std::string title;
  int released;

public:
  Song(const std::string &title, const int &released);

  const bool operator==(const Song& other) const;

  const bool operator!=(const Song& other) const;

  const std::string &getTitle() const;

  int getReleased() const;
};

#endif
