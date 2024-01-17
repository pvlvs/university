#include "song.h"

Song::Song(const std::string &title, const int &released) : title(title), released(released){};

const std::string &Song::getTitle() const { return title; }

int Song::getReleased() const { return released; }
