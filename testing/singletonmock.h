#pragma once
#include <gtest/gtest.h>

class SingletonMock {
  public:
    SingletonMock *getInstance() {
        if (!instance)
            instance = new SingletonMock();
        return instance;
    }
    void removeInstance() {
        delete instance;
        instance = NULL;
    }

  private:
    SingletonMock() {}
    ~SingletonMock();

    static SingletonMock *instance;
};

SingletonMock *SingletonMock::instance = NULL;
