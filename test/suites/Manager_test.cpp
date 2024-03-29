#include "Manager.h"

#include <string>

#include "../lib/test.h"
#include "Object.h"

const string Manager_test_evt = "TestEvent";
const string Manager_test_wrongEvt = "TestEvent2";

int Manager_test_emittedCount = 0;
void Manager_test() {
  class TestManager : public Manager {
   public:
    TestManager() { this->setType("TestType"); };
    [[nodiscard]] auto isValid(string eventType) const -> bool override {
      return eventType == Manager_test_evt;
    };
  };

  class TestObject : public Object {
   public:
    TestObject() { this->setType("TestObject"); };
    auto eventHandler(const Event* e) -> int override {
      if (e->getType() == Manager_test_evt) {
        Manager_test_emittedCount++;
        return 0;
      }
      return -1;
    };
  };

  test("constructor", []() {
    TestManager manager;
    assert_string("sets correct type", manager.getType(), "TestType");
    assert("isStarted() returns false by default", !manager.isStarted());
  });

  test("startUp/shutDown", []() {
    TestManager manager;
    assert_ok("starts up", manager.startUp());
    assert("sets isStarted", manager.isStarted());

    manager.shutDown();
    assert("updates isStarted after shutdown", !manager.isStarted());
  });

  test("subscribe/unsubscribe", []() {
    TestManager manager;
    TestObject obj;

    assert_ok("subscribes to TestEvent",
              manager.subscribe(&obj, Manager_test_evt));
    assert_fail("cannot subscribe to another event",
                manager.subscribe(&obj, Manager_test_wrongEvt));

    assert_ok("unsubscribes from TestEvent",
              manager.unsubscribe(&obj, Manager_test_evt));

    auto event = Event();

    manager.subscribe(&obj, Manager_test_evt);
    manager.onEvent(&event);
    assert_int("does not trigger for wrong type", Manager_test_emittedCount, 0);

    event.setType(Manager_test_evt);

    obj.setActive(false);
    manager.onEvent(&event);
    assert_int("does not trigger if object is inactive",
               Manager_test_emittedCount, 0);

    obj.setActive(true);
    manager.onEvent(&event);
    assert_int("triggers for correct type", Manager_test_emittedCount, 1);

    assert("returns true for valid events", manager.isValid(Manager_test_evt));
    assert("returns false for wrong events",
           !manager.isValid(Manager_test_wrongEvt));
  });
}