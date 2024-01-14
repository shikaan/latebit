#pragma once

#include <string>

#include "Colors.h"
#include "Frame.h"
#include "Vector.h"

namespace df {
enum Slowdown {
  STOANIMATION = 0,
  NO_SLOWDOWN = 1,
};

class Sprite {
 private:
  int width;
  int height;
  int max_frame_count;
  int frame_count;
  int slowdown;
  Color color;
  Frame* frames;
  std::string label;
  char transparency_char;
  Sprite();

 public:
  ~Sprite();
  Sprite(int max_frames);
  Sprite(const Sprite& other);

  void setWidth(int width);
  int getWidth() const;

  void setHeight(int height);
  int getHeight() const;

  void setColor(Color color);
  Color getColor() const;

  void setLabel(std::string label);
  std::string getLabel() const;

  void setSlowdown(int slowdown);
  int getSlowdown() const;

  void setTransparencyChar(char transparency_char);
  char getTransparencyChar() const;

  int getFrameCount() const;
  int addFrame(Frame frame);
  Frame getFrame(int frame_number) const;

  int draw(int frame_number, Vector position) const;
};

}  // namespace df
