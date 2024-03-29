#include "EventStep.h"

namespace lb {
EventStep::EventStep(int count) {
  setType(STEP_EVENT);
  this->stepCount = count;
}

void EventStep::setStepCount(int c) { this->stepCount = c; }
auto EventStep::getStepCount() const -> int { return this->stepCount; }
}  // namespace lb
