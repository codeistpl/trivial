/*
MIT License
Copyright (c) [2018] [Michal Sopniewski]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once

namespace trivial {

template <typename T> class shared_ptr {
public:
  shared_ptr() {
    mCounter = new size_t(0);
    mPtr = NULL;
  };

  shared_ptr(const shared_ptr<T> &rhs) {
    mPtr = rhs.mPtr;
    mCounter = rhs.mCounter;
    *mCounter++;
  }

  shared_ptr(T *ptr) {
    mPtr = ptr;
    mCounter = new size_t(1);
  }

  ~shared_ptr() {
    *mCounter--;
    if (*mCounter <= 1) {
      delete mCounter;
      delete mPtr;
      mPtr == NULL;
    }
  }

  shared_ptr<T> &operator=(T *rhs) {
    if (*mCounter <= 1) {
      delete mCounter;
      delete mPtr;
    }

    mPtr = rhs;
    mCounter = new size_t(1);
    return *this;
  }

  T *get() { return mPtr; }

private:
  T *mPtr;
  size_t *mCounter;
};

} // namespace trivial
