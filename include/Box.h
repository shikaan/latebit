#pragma once

#include <string>

#include "Vector.h"

namespace df {
class Box {
 private:
  Vector top_left_corner;
  float width;
  float height;

 public:
  Box();
  Box(Vector top_left, float width, float height);

  void setCorner(Vector corner);
  Vector getCorner() const;

  void setWidth(float width);
  float getWidth() const;

  void setHeight(float height);
  float getHeight() const;

  bool operator==(const Box &other) const;
  std::string toString() const;
};
}  // namespace df

