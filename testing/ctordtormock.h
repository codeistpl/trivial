#pragma once

class CtorDtorMock {
  public:
    CtorDtorMock() { dtor_triggered = false; }
    ~CtorDtorMock() { dtor_triggered = true; }

    static bool dtor_triggered;
};
