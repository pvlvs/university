#include "rt.h"

const int RomanTransformer::operator[](const std::string &str) const {
  if (!str.length()) {
    throw std::invalid_argument("The passed string is not a roman number");
  }

  int ret = 0;

  for (int i = 0; i < str.length(); i++) {
    if (!map.count(str[i])) {
      throw std::invalid_argument(
          "The passed string contains an invalid character");
    }

    int curr = map.at(str[i]);

    if (i + 1 < str.length()) {
      int next = map.at(str[i + 1]);

      if (next > curr) {
        curr = next - curr;
        i++;
      }
    }

    ret += curr;
  }

  return ret;
};
