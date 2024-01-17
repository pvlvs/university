#include "song.h"

Song::Song(const std::string &title, const int &released)
    : title(title), released(released){};

const bool Song::operator==(const Song &other) const {
    if (other.getTitle() != title) {
        return false;
    }
    if (other.getReleased() != released) {
        return false;
    }

    return true;
};

const bool Song::operator!=(const Song &other) const {
    return !(*this == other);
}

const std::string &Song::getTitle() const { return title; }

int Song::getReleased() const { return released; }
