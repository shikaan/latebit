#include "test.h"

#include <iostream>
#include <regex>

#include "Clock.h"
#include "Vector.h"
#include "colors.h"
#include "test.h"
#include "utils.h"

using namespace std;
using namespace lb;

int ASSERTIONS = 0;
auto getAssertions() -> string { return to_string(ASSERTIONS); }

int FAILED_ASSERTIONS = 0;
auto getFailedAssertions() -> int { return FAILED_ASSERTIONS; }

Clock c = Clock();
auto getClock() -> Clock { return c; }

bool FAILED_ONLY = getenv("FAILED_ONLY") && stoi(getenv("FAILED_ONLY")) == 1;
string FOCUS = getenv("FOCUS") != nullptr ? getenv("FOCUS") : "";

auto assert(const string name, bool assertion, const string message) -> int {
  ASSERTIONS++;

  if (!assertion) {
    cout << red("    ✗ " + name) << endl;
    cout << "      " << message << endl;
    FAILED_ASSERTIONS++;
    return 1;
  }

  if (!FAILED_ONLY) cout << green("    ✓ " + name) << endl;
  return 0;
}

auto assert_string(string name, string got, string want) -> int {
  const bool assertion = got.compare(want) == 0;

  string message = "wanted '" + want + "' got '" + got + "'";

  return assert(name, assertion, message);
}

auto assert_regex(string name, string want, string pattern) -> int {
  regex expression(pattern);
  const bool assertion = regex_match(want, expression);

  string message =
    "string '" + want + "' doesn't match pattern  '" + pattern + "'";

  return assert(name, assertion, message);
}

auto assert_float(string name, float got, float want) -> int {
  string message =
    "wanted '" + to_string(want) + "' got '" + to_string(got) + "'";

  return assert(name, equals(got, want), message);
}

auto assert_int(string name, int got, int want) -> int {
  string message =
    "wanted '" + to_string(want) + "' got '" + to_string(got) + "'";

  return assert(name, got == want, message);
}

auto assert_ok(string name, int got) -> int { return assert_int(name, got, 0); }
auto assert_fail(string name, int got) -> int {
  return assert_int(name, got, -1);
}

auto assert_vector(string name, Vector got, Vector want) -> int {
  return assert(name, got == want,
                "wanted " + want.toString() + " got " + got.toString());
}

auto assert_box(string name, Box got, Box want) -> int {
  return assert(name, got == want,
                "wanted " + want.toString() + " got " + got.toString());
}

void timing(float delta) {
  if (delta > 1000) {
    printf("      Duration: %.2fms\n", delta / 1000);
  } else {
    printf("      Duration: %.2fμs\n", delta);
  }
}

auto suite(std::string name, int (*test)()) -> int {
  if (!FOCUS.empty() && FOCUS != name) {
    std::cout << yellow(name + " (skip)\n");
    return 0;
  }

  static int result = 0;

  std::cout << yellow("\n" + name + "\n");
  result += test();
  timing(c.delta());

  return result;
}

auto suite(std::string name, void (*test)()) -> void {
  if (!FOCUS.empty() && FOCUS != name) {
    std::cout << yellow(name + " (skip)\n");
    return;
  }

  std::cout << yellow("\n" + name + "\n");
  test();
  timing(c.delta());
}

auto test(std::string name, void (*test)()) -> void {
  std::cout << "  " + name + "\n";
  test();
}

auto test(std::string name, int (*test)()) -> int {
  int result = 0;

  std::cout << "  " + name + "\n";
  result += test();

  return result;
}