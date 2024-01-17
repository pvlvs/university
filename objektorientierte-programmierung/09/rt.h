#ifndef rt_h
#define rt_h
#include <iostream>
#include <unordered_map>

class RomanTransformer {
  std::unordered_map<char, int> map = {{'I', 1},   {'V', 5},   {'X', 10},
                                       {'L', 50},  {'C', 100}, {'D', 500},
                                       {'M', 1000}};

public:
  const int operator[](const std::string &str) const;
};

#endif
