#include "../include/Box.h"

#include "../include/Vector.h"
#include "Box_test.h"
#include "test.h"

auto defaultConstructor_test() -> int {
  printf("defaultConstructor_test\n");
  df::Box box;
  int result =
    assert_vector("default constructor sets top left corner to (0, 0)",
                  box.getCorner(), df::Vector());
  result +=
    assert_float("default constructor sets width to 0", box.getWidth(), 0);
  result +=
    assert_float("default constructor sets height to 0", box.getHeight(), 0);
  return result;
}

auto parameterizedConstructor_test() -> int {
  printf("parameterizedConstructor_test\n");
  df::Vector toleft(1, 2);
  float width = 3.5;
  float height = 4.5;
  df::Box box(toleft, width, height);

  int result =
    assert_vector("parameterized constructor sets top left corner correctly",
                  box.getCorner(), toleft);
  result += assert_float("parameterized constructor sets width correctly",
                         box.getWidth(), width);
  result += assert_float("parameterized constructor sets height correctly",
                         box.getHeight(), height);
  return result;
}

auto setCorner_test() -> int {
  printf("setCorner_test\n");
  df::Box box;
  df::Vector corner(5, 6);
  box.setCorner(corner);
  return assert_vector("sets top left corner correctly", box.getCorner(),
                       corner);
}

auto setWidth_test() -> int {
  printf("setWidth_test\n");
  df::Box box;
  float width = 10.5;
  box.setWidth(width);
  return assert_float("sets width correctly", box.getWidth(), width);
}

auto setHeight_test() -> int {
  printf("setHeight_test\n");
  df::Box box;
  float height = 15.5;
  box.setHeight(height);
  return assert_float("sets height correctly", box.getHeight(), height);
}

auto Box_test() -> int {
  int result = 0;
  result += defaultConstructor_test();
  result += parameterizedConstructor_test();
  result += setCorner_test();
  result += setWidth_test();
  result += setHeight_test();
  return result;
}