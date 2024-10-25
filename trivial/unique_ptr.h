/*
MIT License
Copyright (c) [2024] [Michal Sopniewski]

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

#include "trivial/shared_ptr.h"
namespace trivial {

template <typename T> class unique_ptr {
  public:
    unique_ptr(T *ptr) { mPtr = ptr; }

    unique_ptr() { mPtr = NULL; }

    ~unique_ptr() { delete mPtr; }

    T &operator*() { return *mPtr; }
    T &operator->() { return *mPtr; }

    unique_ptr<T> &operator=(T *rhs) {
        if (mPtr != NULL)
            delete mPtr;
        mPtr = rhs;
        return *this;
    }

    T *get() const { return mPtr; }

    operator bool() const { return mPtr != NULL; }

    T *release() {
        T *ptr = mPtr;
        mPtr = NULL;
        return ptr;
    }

    void reset() {
        delete mPtr;
        mPtr = NULL;
    }

    void swap(unique_ptr<T> &rhs) {
        T *tmp = mPtr;
        mPtr = rhs.mPtr;
        rhs.mPtr = tmp;
    }

  private:
    T *mPtr;
};

} // namespace trivial