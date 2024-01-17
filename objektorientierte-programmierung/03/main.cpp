#include <assert.h>
#include <iostream>

namespace app {

class Song {
  std::string title;
  int released;

public:
  void set(const std::string &title, int released) {
    this->title = title;
    this->released = released;
  }

  const std::string &getTitle() const { return title; }

  int getReleased() const { return released; }
};

class Band {
  std::string name;
  int founded;
  Song mostPopular;

public:
  void set(const std::string &name, const int founded,
           const Song &mostPopular) {
    this->name = name;
    this->founded = founded;
    this->mostPopular = mostPopular;
  }

  const std::string &getName() const { return name; }

  const int &getFounded() const { return founded; }

  const Song &getMostPopular() const { return mostPopular; }

  int compare(const Band &other) const { return other.getFounded() - founded; };
};

Band createBand() {
  Song satisfaction;
  satisfaction.set("Satisfaction", 1965);

  Band band;
  band.set("The Rolling Stones", 1962, satisfaction);

  return band;
}

void testGetters() {
  app::Band band = app::createBand();
  assert(band.getName() == "The Rolling Stones");
  assert(band.getFounded() == 1962);

  app::Song mostPopular = band.getMostPopular();
  assert(mostPopular.getTitle() == "Satisfaction");
  assert(mostPopular.getReleased() == 1965);
}

void testCompare() {
  app::Song songBand;
  app::Song songOther;

  app::Band band;
  app::Band other;

  songBand.set("Rolling Rolling", 1995);
  band.set("Die Rollenden Steine", 1984, songBand);

  songOther.set("Dam", 2003);
  other.set("The Otters", 1999, songOther);

  assert(band.compare(other) == 1999 - 1984);
  assert(other.compare(band) == 1984 - 1999);

  songBand.set("Berg Runter", 2003);
  band.set("Die Berge", 1999, songOther);

  assert(band.compare(other) == 0);
  assert(other.compare(band) == 0);

  songBand.set("He's comming", -1);
  band.set("The Olds", -4, songBand);

  songOther.set("There he is", 1);
  other.set("The News", 1, songOther);

  assert(band.compare(other) == 1 - -4);
  assert(other.compare(band) == -4 - 1);
}

} // namespace app

int main() {
  std::cout << "Hello World!" << std::endl;

  app::testGetters();
  app::testCompare();

  std::cout << "Goodbye!" << std::endl;

  return 0;
}
