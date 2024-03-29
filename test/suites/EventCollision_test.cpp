#include "EventCollision.h"

#include "../lib/test.h"

using namespace lb;

void EventCollision_test() {
  EventCollision subject;
  assert("sets default object1", subject.getFirstObject() == nullptr);
  assert("sets default object2", subject.getSecondObject() == nullptr);
  assert_vector("sets default position", subject.getPos(), Vector());

  Object obj1, obj2;
  Vector pos(1, 1);
  subject = EventCollision(&obj1, &obj2, pos);
  assert("sets correct object1", subject.getFirstObject() == &obj1);
  assert("sets correct object2", subject.getSecondObject() == &obj2);
  assert_vector("sets correct position", subject.getPos(), pos);

  Object obj3;
  subject.setFirstObject(&obj3);
  assert("sets correct object1", subject.getFirstObject() == &obj3);

  Object obj4;
  subject.setSecondObject(&obj4);
  assert("sets correct object2", subject.getSecondObject() == &obj4);

  Vector pos2(2, 2);
  subject.setPosition(pos2);
  assert_vector("sets correct position", subject.getPos(), pos2);
}