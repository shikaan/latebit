#include "Animation.h"

#include "../lib/test.h"
#include "Box.h"
#include "DisplayManager.h"
#include "ResourceManager.h"
#include "Sprite.h"
#include "Vector.h"

using namespace std;

void setSprite_test() {
  Animation animation;
  RM.loadTextSprite("test/fixtures/correct.txt", "sprite");
  Sprite *sprite = RM.getSprite("sprite");
  animation.setIndex(1);
  animation.setSlowdownCount(1);
  animation.setSprite(sprite);

  assert("sets sprite", animation.getSprite() == sprite);
  assert_int("resets index", animation.getIndex(), 0);
  assert_int("resets slowdown count", animation.getSlowdownCount(), 0);
}

void setName_test() {
  Animation animation;
  animation.setName("animation");
  assert_string("sets name", animation.getName(), "animation");
}

void setIndex_test() {
  Animation animation;
  animation.setIndex(5);
  assert_int("sets index", animation.getIndex(), 5);
}

void setSlowdownCount_test() {
  Animation animation;
  animation.setSlowdownCount(3);
  assert_int("sets slowdown count", animation.getSlowdownCount(), 3);
}

void draw_test() {
  auto filename = "test/fixtures/correct.txt";
  auto label = "sprite";

  RM.loadTextSprite(filename, label);
  Sprite *sprite = RM.getSprite(label);

  Animation animation;
  animation.setSprite(sprite);

  assert_ok("draws the frame", animation.draw(Vector()));
  assert_int("does't update index before slowdown", animation.getIndex(), 0);
  assert_int("slowdown count is updated", animation.getSlowdownCount(), 1);
  assert_ok("draws the frame", animation.draw(Vector()));
  assert_int("index is updated", animation.getIndex(), 1);
  assert_int("slowdown is updated", animation.getSlowdownCount(), 0);

  // Test animation slowdown
  animation.setSlowdownCount(STOP_ANIMATION_SLOWDOWN);
  assert_ok("draws the frame", animation.draw(Vector()));
  assert_int("index is not updated", animation.getIndex(), 1);
  assert_int("slowdown is not updated", animation.getSlowdownCount(),
             STOP_ANIMATION_SLOWDOWN);

  RM.shutDown();
  RM.startUp();
}

void getBox_test() {
  auto animation = Animation();
  auto unitBox = Box(Vector(), 1.0, 1.0);
  assert_box("returns unit box", animation.getBox(), unitBox);

  auto filename = "test/fixtures/correct.txt";
  auto label = "label";
  RM.loadTextSprite(filename, label);
  Sprite *sprite = RM.getSprite(label);
  animation.setSprite(sprite);

  auto want = Box(Vector(), 3.0, 4.0);
  auto animBox = animation.getBox();
  assert_box("returns correct box", animBox, want);
}

void Animation_test() {
  DM.startUp();
  RM.startUp();
  test("setSprite", setSprite_test);
  test("setName", setName_test);
  test("setIndex", setIndex_test);
  test("setSlowdownCount", setSlowdownCount_test);
  test("draw", draw_test);
  test("getBox", getBox_test);
  RM.shutDown();
  RM.startUp();
  DM.shutDown();
  DM.startUp();
}