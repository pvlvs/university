#include "band.h"
#include "song.h"
#include <assert.h>
#include <iostream>

namespace app {

const Band createBand() {
  Song satisfaction("Satisfaction", 1965);
  Band band("The Rolling Stones", 1962, satisfaction);

  return band;
}

void sort(Band *band, const int length) {
  if (length < 2) {
    throw std::invalid_argument("Parameter len must be greater than one.");
  } else if (band == NULL) {
    throw std::invalid_argument("Parameter band can't be an empty array.");
  }

  Band temp = band[0];

  for (int i = 0; i < length; i++) {
    for (int j = 0; j < length; j++) {
      if (band[i].compare(band[j]) > 0) {
        temp = band[j];
        band[j] = band[i];
        band[i] = temp;
      }
    }
  }

  temp = createBand();
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

  for (int i = 0; i < 5; i++) {
    assert(bands[i].getSize() == 0);
  }

  sort(bands, 5);

  for (int i = 0; i < 5; i++) {
    assert(bands[i].getSize() == 0);
  }

  assert(bands[0].getFounded() == 1999);
  assert(bands[1].getFounded() == 2000);
  assert(bands[2].getFounded() == 2001);
  assert(bands[3].getFounded() == 2002);
  assert(bands[4].getFounded() == 2003);

  try {
    sort(bands, -2);
    assert(false);
  } catch (std::invalid_argument &e) {
    assert(std::string("Parameter len must be greater than one.")
               .compare(e.what()) == 0);
  } catch (...) {
    assert(false);
  }

  try {
    sort({}, 3);
    assert(false);
  } catch (std::invalid_argument &e) {
    assert(std::string("Parameter band can't be an empty array.")
               .compare(e.what()) == 0);
  } catch (...) {
    assert(false);
  }
}

void testSortMembers() {
  std::string members1[]{"Tom", "Jerry"};
  std::string members2[]{"Tick", "Trick", "Track"};

  Song song = Song("Song", 1999);
  Band band1 = Band("Band 2", 2000, song, members1, 2);
  Band band2 = Band("Band 3", 2001, song, members2, 3);

  for (int i = 0; i < 2; i++) {
    assert(band1.getMember(i) == members1[i]);
  }
  try {
    band1.getMember(2);
    assert(false);
  } catch (std::invalid_argument &e) {
    assert(std::string("index can't be bigger than size").compare(e.what()) ==
           0);
  } catch (...) {
    assert(false);
  }

  for (int i = 0; i < 3; i++) {
    assert(band2.getMember(i) == members2[i]);
  }
  try {
    band2.getMember(3);
    assert(false);
  } catch (std::invalid_argument &e) {
    assert(std::string("index can't be bigger than size").compare(e.what()) ==
           0);
  } catch (...) {
    assert(false);
  }

  Band bands[2] = {band2, band1};

  for (int i = 0; i < 2; i++) {
    assert(bands[i].getSize() == 3 - i);
  }

  sort(bands, 2);

  for (int i = 0; i < 2; i++) {
    assert(band1.getMember(i) == members1[i]);
  }
  try {
    band1.getMember(2);
    assert(false);
  } catch (std::invalid_argument &e) {
    assert(std::string("index can't be bigger than size").compare(e.what()) ==
           0);
  } catch (...) {
    assert(false);
  }
  for (int i = 0; i < 3; i++) {
    assert(band2.getMember(i) == members2[i]);
  }
  try {
    band2.getMember(3);
    assert(false);
  } catch (std::invalid_argument &e) {
    assert(std::string("index can't be bigger than size").compare(e.what()) ==
           0);
  } catch (...) {
    assert(false);
  }

  assert(bands[0].getSize() == 2);
  assert(bands[0].getFounded() == 2000);
  assert(bands[1].getSize() == 3);
  assert(bands[1].getFounded() == 2001);

  try {
    sort(bands, -2);
    assert(false);
  } catch (std::invalid_argument &e) {
    assert(std::string("Parameter len must be greater than one.")
               .compare(e.what()) == 0);
  } catch (...) {
    assert(false);
  }

  try {
    sort({}, 3);
    assert(false);
  } catch (std::invalid_argument &e) {
    assert(std::string("Parameter band can't be an empty array.")
               .compare(e.what()) == 0);
  } catch (...) {
    assert(false);
  }
}

void testConstructor() {
  Song satisfaction("Satisfaction", 1965);
  std::string members[]{"Jagger", "Richards", "Wood"};
  Band stones("The Rolling Stones", 1962, satisfaction, members, 3);

  assert(stones.getSize() == 3);
  assert(stones.getMember(0) == members[0]);
  assert(stones.getMember(1) == members[1]);
  assert(stones.getMember(2) == members[2]);

  members[0] = "Duck";

  assert(stones.getMember(0) == "Jagger");

  try {
    Band stones("The Rolling Stones", 1962, satisfaction, members, -1);
    assert(false);
  } catch (...) {
  }

  try {
    Band stones("The Rolling Stones", 1962, satisfaction, nullptr, 3);
    assert(false);
  } catch (...) {
  }
}

void testGetMember() {
  Song satisfaction("Satisfaction", 1965);
  std::string members[]{"Jagger", "Richards", "Wood"};
  Band stones("The Rolling Stones", 1962, satisfaction, members, 3);

  try {
    stones.getMember(5);
    assert(false);
  } catch (std::invalid_argument &e) {
    assert(std::string("index can't be bigger than size").compare(e.what()) ==
           0);
  } catch (...) {
    assert(false);
  }

  try {
    stones.getMember(-1);
    assert(false);
  } catch (std::invalid_argument &e) {
    assert(std::string("index can't be negative").compare(e.what()) == 0);
  } catch (...) {
    assert(false);
  }

  Band phones("The Rolling Phones", 1962, satisfaction);

  try {
    phones.getMember(1);
    assert(false);
  } catch (std::invalid_argument &e) {
    assert(std::string("Size is zero. There is nothing to set or get")
               .compare(e.what()) == 0);
  } catch (...) {
    assert(false);
  }
}

void testSetMember() {
  Song satisfaction("Satisfaction", 1965);
  std::string members[]{"Jagger", "Richards", "Wood"};
  Band stones("The Rolling Stones", 1962, satisfaction, members, 3);

  stones.setMember(0, "Duck");
  assert(stones.getMember(0) == "Duck");

  try {
    stones.setMember(5, "Don");
    assert(false);
  } catch (std::invalid_argument &e) {
    assert(std::string("index can't be bigger than size").compare(e.what()) ==
           0);
  } catch (...) {
    assert(false);
  }

  try {
    stones.setMember(-1, "Don");
    assert(false);
  } catch (std::invalid_argument &e) {
    assert(std::string("index can't be negative").compare(e.what()) == 0);
  } catch (...) {
    assert(false);
  }

  Band phones("The Rolling Phones", 1962, satisfaction);

  try {
    phones.setMember(1, "Smart");
    assert(false);
  } catch (std::invalid_argument &e) {
    assert(std::string("Size is zero. There is nothing to set or get")
               .compare(e.what()) == 0);
  } catch (...) {
    assert(false);
  }
}

void testCopyConstructor() {
  Song satisfaction("Satisfaction", 1965);
  std::string members[]{"Jagger", "Richards", "Wood"};
  Band stones("The Rolling Stones", 1962, satisfaction, members, 3);

  Band copy = stones;
  stones.setMember(0, "Duck");

  assert(copy.getMember(0) == "Jagger");
}

void testOperators() {
  Song satisfaction("Satisfaction", 1965);
  std::string members[]{"Jagger", "Richards", "Wood"};
  Band stones("The Rolling Stones", 1962, satisfaction, members, 3);
  assert(stones == stones);
  Band copy = stones;
  assert(stones == copy);
  assert(copy == stones);
  Song ruby("Ruby Tuesday", 1967);
  Band stonesRuby("The Rolling Stones", 1962, ruby, members, 3);
  assert(stones != stonesRuby);
  assert(stonesRuby != stones);
  Band noWood("The Rolling Stones", 1962, satisfaction, members, 2);
  assert(stones != noWood);
  assert(noWood != stones);
  copy.setMember(0, "Richards");
  copy.setMember(1, "Jagger");
  assert(stones != copy);
  assert(copy != stones);
}

void testAddMember() {
  Song satisfaction("Satisfaction", 1965);
  std::string members[]{"Jagger", "Richards", "Wood"};
  Band stones("The Rolling Stones", 1962, satisfaction, members, 3);
  stones.addMember("Duck");
  assert(stones.getMember(3) == "Duck");
}
} // namespace app

std::ostream &operator<<(std::ostream &out, const Band &other) {
  out << "name: " << other.getName() << ", ";
  out << "founded: " << other.getFounded() << ", ";
  out << "members: ";

  for (int i = 0; i < other.getSize(); i++) {
    out << other.getMember(i) << ", ";
  }

  out << "most popular song: title: " << other.getMostPopular().getTitle()
      << ", released: " << other.getMostPopular().getReleased();

  return out;
}

int main() {
  std::cout << "Hi!" << std::endl;

  app::testGetters();
  app::testCompare();
  app::testSort();
  app::testSortMembers();
  app::testConstructor();
  app::testSetMember();
  app::testGetMember();
  app::testCopyConstructor();
  app::testOperators();

  Song satisfaction("Satisfaction", 1965);
  std::string members[]{"Jagger", "Richards", "Wood"};
  Band stones("The Rolling Stones", 1962, satisfaction, members, 3);
  std::cout << stones << std::endl;

  std::cout << "Bye." << std::endl;

  return 0;
}
