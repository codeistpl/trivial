#pragma once
#include <gmock/gmock.h>

class CtorDtorMock {
  public:
    CtorDtorMock() {}
    ~CtorDtorMock() { dtor(); }

    MOCK_METHOD0(dtor, void());
};
