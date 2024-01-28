#include "ViewObject.h"

#include "DisplayManager.h"
#include "EventView.h"
#include "SceneGraph.h"
#include "Vector.h"
#include "WorldManager.h"
#include "utils.h"

namespace df {

ViewObject::ViewObject() {
  setType("ViewObject");
  setSolidness(SPECTRAL);
  setAltitude(MAX_ALTITUDE);

  subscribe(VIEW_EVENT);
}

auto ViewObject::getDisplayString() -> string {
  return label + ": " + to_string(value);
}

auto ViewObject::draw() -> int {
  // TODO maybe we can cache the view position instead of recalculating it every
  // time and calculate the world position based on that
  refresh();
  return DM.drawString(getPosition(), getDisplayString(), ALIGN_LEFT, color);
}

auto ViewObject::eventHandler(const Event* p_e) -> int {
  if (p_e->getType() == VIEW_EVENT) {
    auto viewEvent = dynamic_cast<const EventView*>(p_e);
    if (viewEvent->getObjectType() == getType()) {
      if (viewEvent->getDelta()) {
        setValue(getValue() + viewEvent->getValue());
      } else {
        setValue(viewEvent->getValue());
      }
      return 1;
    }
  }
  return 0;
}

auto ViewObject::refresh() -> void {
  // Update the bounding box depending on the content
  auto width = getDisplayString().size();
  auto height = 1;
  this->setBox(Box(Vector(), width, height));

  // Update the position depending on the location
  float textWidth = getBox().getWidth();
  float textHeight = getBox().getHeight();
  float viewWidth = WM.getView().getWidth();
  float viewHeight = WM.getView().getHeight();

  float x = 0, y = 0;
  switch (this->location) {
    case TOP_LEFT:
      break;
    case TOP_CENTER:
      x = (viewWidth / 2) - (textWidth / 2);
      break;
    case TOP_RIGHT:
      x = viewWidth - textWidth;
      break;
    case CENTER_LEFT:
      y = (viewHeight / 2) - (textHeight / 2);
      break;
    case CENTER_CENTER:
      x = (viewWidth / 2) - (textWidth / 2);
      y = (viewHeight / 2) - (textHeight / 2);
      break;
    case CENTER_RIGHT:
      x = viewWidth - textWidth;
      y = (viewHeight / 2) - (textHeight / 2);
      break;
    case BOTTOM_LEFT:
      x = 0;
      y = viewHeight - textHeight;
      break;
    case BOTTOM_CENTER:
      x = (viewWidth / 2) - (textWidth / 2);
      y = viewHeight - textHeight;
      break;
    case BOTTOM_RIGHT:
      x = viewWidth - textWidth;
      y = viewHeight - textHeight;
      break;
  }

  x = clamp(x, 0, viewWidth - textWidth);
  y = clamp(y, 0, viewHeight - textHeight);

  auto position = viewToWorld(Vector(x, y));
  setPosition(position);
}

auto ViewObject::setLocation(ViewObjectLocation l) -> void {
  this->location = l;
}
auto ViewObject::getLocation() const -> ViewObjectLocation { return location; }

auto ViewObject::setValue(int value) -> void { this->value = value; }
auto ViewObject::getValue() const -> int { return value; }

auto ViewObject::setColor(Color color) -> void { this->color = color; }
auto ViewObject::getColor() const -> Color { return color; }

auto ViewObject::setLabel(string label) -> void { this->label = label; }
auto ViewObject::getLabel() const -> string { return label; }

}  // namespace df