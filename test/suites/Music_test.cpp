#include "Music.h"

#include "../lib/test.h"
#include "AudioManager.h"

void Music_test() {
  AM.startUp();

  test("constructor", []() {
    Music music;
    assert("sets empty label", music.getLabel().empty());
  });

  test("setters", []() {
    Music music;
    music.setLabel("Background Music");
    assert("setLabel() and getLabel()", music.getLabel() == "Background Music");
  });

  test("loadMusic", []() {
    Music music;
    assert_ok("succeeds with valid file",
              music.loadMusic("test/fixtures/sound.wav"));
    assert_fail("fails with invalid file",
                music.loadMusic("invalid_sound.wav"));
  });

  AM.shutDown();
  AM.startUp();
}