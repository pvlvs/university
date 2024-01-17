#ifndef searcher_h
#define searcher_h

#include <vector>

template <typename T> class Searcher {
  std::vector<T> keys;

public:
  Searcher(T *keys, int size) : keys(std::vector<T>(keys, keys + size)){};

  const bool contains(const T &key) {
    for (int i = 0; i < keys.size(); i++) {
      if (key == keys[i]) {
        if (i > 0) {
          int j = i - 1;

          T temp = keys[i];
          keys[i] = keys[j];
          keys[j] = temp;
        }

        return true;
      }
    }

    return false;
  }
};

#endif
