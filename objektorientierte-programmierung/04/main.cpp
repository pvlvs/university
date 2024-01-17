#include "band.h"
#include "song.h"
#include <assert.h>
#include <iostream>

namespace app {

enum Direction { Ascending, Descending };

const Band createBand() {
  Song satisfaction("Satisfaction", 1965);
  Band band("The Rolling Stones", 1962, satisfaction);

  return band;
}

void sort(Band *band, const int length,
          const Direction direction = Descending) {
  if (length < 2) {
    throw std::invalid_argument("Parameter len must be greater than one.");
  } else if (band == NULL) {
    throw std::invalid_argument("Parameter band can't be an empty array.");
  }

  for (int i = 0; i < length; i++) {
    for (int j = 0; j < length; j++) {
      if (direction == Ascending && band[i].compare(band[j]) > 0) {
        Band temp = band[j];
        band[j] = band[i];
        band[i] = temp;
      } else if (direction == Descending && band[i].compare(band[j]) < 0) {
        Band temp = band[i];
        band[i] = band[j];
        band[j] = temp;
      }
    }
  }
}

void testGetters() {
  Band band = createBand();
  assert(band.getName() == "The Rolling Stones");
  assert(band.getFounded() == 1962);

  Song mostPopular = band.getMostPopular();
  assert(mostPopular.getTitle() == "Satisfaction");
  assert(mostPopular.getReleased() == 1965);
}

void testCompare() {
  Song rollingRolling("Rolling Rolling", 1995);
  Band rollendeSteine("Die Rollenden Steine", 1984, rollingRolling);

  Song dam("Dam", 2003);
  Band otters("The Otters", 1999, dam);

  assert(rollendeSteine.compare(otters) == 1999 - 1984);
  assert(otters.compare(rollendeSteine) == 1984 - 1999);

  Song bergRunter("Berg Runter", 2003);
  Band berge("Die Berge", 1999, bergRunter);

  assert(berge.compare(otters) == 0);
  assert(otters.compare(berge) == 0);

  Song comming("He's comming", -1);
  Band olds("The Olds", -4, comming);

  Song thereHeIs("There he is", 1);
  Band news("The News", 1, thereHeIs);

  assert(olds.compare(news) == 1 - -4);
  assert(news.compare(olds) == -4 - 1);
}

void testSort() {
  Song song = Song("Song", 1999);

  Band bands[5] = {Band("Band 2", 2000, song), Band("Band 5", 2003, song),
                   Band("Band 3", 2001, song), Band("Band 1", 1999, song),
                   Band("Band 4", 2002, song)};

  app::sort(bands, 5);

  int length = sizeof(bands) / sizeof(bands[0]);
  assert(length == 5);

  assert(bands[0].getFounded() == 2003);
  assert(bands[1].getFounded() == 2002);
  assert(bands[2].getFounded() == 2001);
  assert(bands[3].getFounded() == 2000);
  assert(bands[4].getFounded() == 1999);

  app::sort(bands, 5, Ascending);

  length = sizeof(bands) / sizeof(bands[0]);
  assert(length == 5);

  assert(bands[0].getFounded() == 1999);
  assert(bands[1].getFounded() == 2000);
  assert(bands[2].getFounded() == 2001);
  assert(bands[3].getFounded() == 2002);
  assert(bands[4].getFounded() == 2003);

  try {
    app::sort(bands, -2);
    assert(false);
  } catch (std::invalid_argument &e) {
    assert(std::string("Parameter len must be greater than one.")
               .compare(e.what()) == 0);
  } catch (...) {
    assert(false);
  }

  try {
    app::sort({}, 3);
    assert(false);
  } catch (std::invalid_argument &e) {
    assert(std::string("Parameter band can't be an empty array.")
               .compare(e.what()) == 0);
  } catch (...) {
    assert(false);
  }
}
} // namespace app

int main() {
  std::cout << "Hello World!" << std::endl;

  app::testGetters();
  app::testCompare();
  app::testSort();

  std::cout << "Goodbye!" << std::endl;

  return 0;
}
