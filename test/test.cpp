#include "test.h"

#include <iostream>
#include <regex>
#include <sstream>

#include "../src/Vector.h"
#include "test.h"

int ASSERTIONS = 0;
int getAssertions() { return ASSERTIONS; }

int assert(const std::string name, bool assertion, const std::string message) {
  ASSERTIONS++;

  if (!assertion) {
    std::cout << "FAIL: " << name << std::endl;
    std::cout << "      " << message << std::endl;
    return 1;
  }

  std::cout << " OK : " << name << std::endl;
  return 0;
}

int assert_string(std::string name, std::string got, std::string want) {
  const bool assertion = got.compare(want) == 0;

  std::string message = "wanted '" + want + "' got '" + got + "'";

  return assert(name, assertion, message);
}

int assert_regex(std::string name, std::string want, std::string pattern) {
  std::regex expression(pattern);
  const bool assertion = std::regex_match(want, expression);

  std::string message =
      "string '" + want + "' doesn't match pattern  '" + pattern + "'";

  return assert(name, assertion, message);
}

int assert_float(std::string name, float got, float want) {
  std::string message =
      "wanted '" + std::to_string(want) + "' got '" + std::to_string(got) + "'";

  return assert(name, got == want, message);
}

int assert_int(std::string name, int got, int want) {
  std::string message =
      "wanted '" + std::to_string(want) + "' got '" + std::to_string(got) + "'";

  return assert(name, got == want, message);
}

int assert_vector(std::string name, df::Vector *p_got, df::Vector *p_want) {
  return assert(name, *p_got == *p_want,
                "wanted " + p_want->toString() + " got " + p_got->toString());
}