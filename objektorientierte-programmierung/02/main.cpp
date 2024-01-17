#include <assert.h>
#include <iostream>

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

void isPrimeTest() {
  assert(!isPrime(321));
  assert(isPrime(3));
  assert(isPrime(2));
  assert(!isPrime(1));
  assert(!isPrime(0));
  assert(!isPrime(-1));
  assert(!isPrime(-2));
  assert(!isPrime(-3));
}

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

void encode(std::string &text) {
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

void encodeTest() {
  // A1
  char charText1[] = "zeta";
  char charExpected1[] = "afub";
  encode(charText1);

  for (uint i = 0; i < 4; i++) {
    assert(charText1[i] == charExpected1[i]);
  }
  assert(charText1[4] == 0);

  char charText2[] = "";
  char charExpected2[] = "";
  encode(charText2);

  assert(charText2[0] == charExpected2[0]);

  char charText3[] = "Haus";
  try {
    encode(charText3);
    assert(false);
  } catch (const std::invalid_argument &e) {
    assert(true);
  } catch (...) {
    assert(false);
  }

  char charText4[] = "löwe";
  try {
    encode(charText4);
    assert(false);
  } catch (const std::invalid_argument &e) {
    assert(true);
  } catch (...) {
    assert(false);
  }

  char charText5[] = "1123";
  try {
    encode(charText5);
    assert(false);
  } catch (const std::invalid_argument &e) {
    assert(true);
  } catch (...) {
    assert(false);
  }

  // A2
  std::string strText1 = "zeta";
  std::string strExpected1 = "afub";
  encode(strText1);
  assert(strText1 == strExpected1);

  std::string strText2 = "";
  std::string strExpected2 = "";
  encode(strText2);
  assert(strText2 == strExpected2);

  std::string strText3 = "Haus";
  try {
    encode(strText3);
    assert(false);
  } catch (const std::invalid_argument &e) {
    assert(true);
  } catch (...) {
    assert(false);
  }

  std::string strText4 = "löwe";
  try {
    encode(strText4);
    assert(false);
  } catch (const std::invalid_argument &e) {
    assert(true);
  } catch (...) {
    assert(false);
  }

  std::string strText5 = "1123";
  try {
    encode(strText5);
    assert(false);
  } catch (const std::invalid_argument &e) {
    assert(true);
  } catch (...) {
    assert(false);
  }
}

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

void decode(std::string &text) {
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

void decodeTest() {
  // A1
  char charText1[] = "afub";
  char charExpected1[] = "zeta";
  decode(charText1);

  for (uint i = 0; i < 4; i++) {
    assert(charText1[i] == charExpected1[i]);
  }
  assert(charText1[4] == 0);

  char charText2[] = "";
  char charExpected2[] = "";
  decode(charText2);

  assert(charText2[0] == charExpected2[0]);

  char charText3[] = "Haus";
  try {
    decode(charText3);
    assert(false);
  } catch (const std::invalid_argument &e) {
    assert(true);
  } catch (...) {
    assert(false);
  }

  char charText4[] = "löwe";
  try {
    decode(charText4);
    assert(false);
  } catch (const std::invalid_argument &e) {
    assert(true);
  } catch (...) {
    assert(false);
  }

  char charText5[] = "1123";
  try {
    decode(charText5);
    assert(false);
  } catch (const std::invalid_argument &e) {
    assert(true);
  } catch (...) {
    assert(false);
  }

  // A2
  std::string strText1 = "afub";
  std::string strExpected1 = "zeta";
  decode(strText1);
  assert(strText1 == strExpected1);

  std::string strText2 = "";
  std::string strExpected2 = "";
  decode(strText2);
  assert(strText2 == strExpected2);

  std::string strText3 = "Haus";
  try {
    decode(strText3);
    assert(false);
  } catch (const std::invalid_argument &e) {
    assert(true);
  } catch (...) {
    assert(false);
  }

  std::string strText4 = "löwe";
  try {
    decode(strText4);
    assert(false);
  } catch (const std::invalid_argument &e) {
    assert(true);
  } catch (...) {
    assert(false);
  }

  std::string strText5 = "1123";
  try {
    decode(strText5);
    assert(false);
  } catch (const std::invalid_argument &e) {
    assert(true);
  } catch (...) {
    assert(false);
  }
}

std::string *copyStrings(const std::string str[], int len) {
  if (len < 0) {
    throw std::invalid_argument("length must be >= 0");
  }

  std::string *ret = new std::string[len];

  for (int i = 0; i < len; i++) {
    ret[i] = str[i];
  }

  return ret;
}

void copyStringsTest() {
  std::string strArr[] = {"one", "two", "three"};
  int len = sizeof(strArr) / sizeof(strArr[0]);
  std::string *strArrCopy = copyStrings(strArr, len);

  for (int i = 0; i < len; i++) {
    assert(strArrCopy[i] == strArr[i]);
  }

  strArr[1] = "changed";

  assert(strArr[1] == "changed");
  assert(strArrCopy[1] == "two");

  std::string strArr2[] = {"", "", ""};
  int len2 = sizeof(strArr2) / sizeof(strArr2[0]);
  std::string *strArr2Copy = copyStrings(strArr2, len2);

  for (int i = 0; i < len2; i++) {
    assert(strArr2Copy[i] == strArr2[i]);
  }

  strArr2[1] = "changed";

  assert(strArr2[1] == "changed");
  assert(strArr2Copy[1] == "");

  std::string strArr3[] = {"a", "", "Ä"};
  int len3 = sizeof(strArr3) / sizeof(strArr3[0]);
  std::string *strArr3Copy = copyStrings(strArr3, len3);

  for (int i = 0; i < len3; i++) {
    assert(strArr3Copy[i] == strArr3[i]);
  }

  strArr3[2] = "changed";

  assert(strArr3[2] == "changed");
  assert(strArr3Copy[2] == "Ä");

  std::string strArr4[] = {"a", "", "Ä", " ", "="};
  int len4 = sizeof(strArr4) / sizeof(strArr4[0]);
  std::string *strArr4Copy = copyStrings(strArr4, len4);

  for (int i = 0; i < len4; i++) {
    assert(strArr4Copy[i] == strArr4[i]);
  }

  strArr4[3] = "changed";

  assert(strArr4[3] == "changed");
  assert(strArr4Copy[3] == " ");

  std::string strArr5[] = {};
  int len5 = sizeof(strArr5) / sizeof(strArr5[0]);
  std::string *strArr5Copy = copyStrings(strArr5, len5);

  for (int i = 0; i < len5; i++) {
    assert(strArr5Copy[i] == strArr5[i]);
  }

  std::string strArr6[] = {"Monkey"};
  int len6 = -1;

  try {
    copyStrings(strArr6, len6);
    assert(false);
  } catch (const std::invalid_argument &e) {
    assert(true);
  } catch (...) {
    assert(false);
  }
}

int main() {
  // A1
  isPrimeTest();
  encodeTest();
  decodeTest();

  // A2
  std::string text = "zeta";
  encode(text);
  std::cout << "Encode: " << text << std::endl;
  decode(text);
  std::cout << "Decode: " << text << std::endl;

  // A3
  std::string strArr[] = {"one", "two", "three"};
  int len = sizeof(strArr) / sizeof(strArr[0]);
  std::string *strArrCopy = copyStrings(strArr, len);
  strArr[1] = "changed";

  for (uint i = 0; i < (*strArr).size(); i++) {
    std::cout << "Original: " << strArr[i] << std::endl;
  }

  for (uint i = 0; i < (*strArrCopy).size(); i++) {
    std::cout << "Copy: " << strArrCopy[i] << std::endl;
  }

  copyStringsTest();

  std::cout << "\nDone." << std::endl;

  return 0;
}
