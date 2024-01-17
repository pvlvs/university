#include <iostream>

// A1 a.
bool isPrime(int n) {
  if (n <= 1) {
    return false;
  }

  bool ret = true;

  for (int i = 2; i < n; i++) {
    if (n % i == 0) {
      ret = false;
      break;
    }
  }

  return ret;
}

// A1 b.
bool showProof() {
  bool proven = true;

  for (int i = 4; i <= 10000; i += 2) {
    bool found = false;

    for (int low = 1; low <= i / 2; low++) {
      int high = i - low;

      if (isPrime(low) && isPrime(high)) {
        found = true;
        break;
      }
    }

    if (!found) {
      proven = false;
      break;
    }
  }

  return proven;
}

// A2 a.
void encode(char *text) {
  int index = 0;

  while (text[index] != 0) {
    if (text[index] < 'a' || text[index] > 'z') {
      throw std::invalid_argument("Text must be all lowercase");
    }

    if (text[index] == 'z') {
      text[index] = 'a';
    } else {
      text[index]++;
    }

    index++;
  }
}

// A2 b.
void decode(char *text) {
  int index = 0;

  while (text[index] != 0) {
    if (text[index] < 'a' || text[index] > 'z') {
      throw std::invalid_argument("Text must be all lowercase");
    }

    if (text[index] == 'a') {
      text[index] = 'z';
    } else {
      text[index]--;
    }

    index++;
  }
}

int main() {
  // A1
  std::cout << "Prime: \t\t" << std::boolalpha << isPrime(3) << std::endl;
  std::cout << "Theorem: \t" << std::boolalpha << showProof() << std::endl;

  // A2
  // a.
  char text[] = "zeta";
  encode(text);
  std::cout << "Encode: \t" << text << std::endl;
  // b.
  decode(text);
  std::cout << "Decode: \t" << text << std::endl;

  std::cout << "Done." << std::endl;

  return 0;
}
