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
      mCounter = NULL;
      mPtr = NULL;
    };

    shared_ptr(const shared_ptr<T> &rhs) {
      mPtr = rhs.mPtr;
      mCounter = rhs.mCounter;
      (*mCounter)++;
    }

    shared_ptr(const T &rhs) {
      mPtr = new T(rhs);
      mCounter = new long(1);
    }

    shared_ptr(T *ptr) {
      mPtr = ptr;
      mCounter = new long(1);
    }

    ~shared_ptr() {
      if(mCounter==NULL)
        return;
      (*mCounter) --;
      if (*mCounter < 1) {
          delete mCounter;
          delete mPtr;
        }
    }

    void reset(){
      if(mCounter != NULL){
          (*mCounter) --;
          mCounter = NULL;
        }
      mPtr = NULL;
    }

    shared_ptr<T> &operator=(T *rhs) {
      if (*mCounter <= 1) {
          delete mCounter;
          delete mPtr;
        }

      mPtr = rhs;
      mCounter = new long(1);
      return *this;
    }

    T& operator*(){
      return *mPtr;
    }

    T* operator->(){
      return mPtr;
    }

    T *get() { return mPtr; }

    long use_count() const{
      if (mCounter == NULL)
        return 0;
      return *mCounter;
    }

    explicit operator bool() const {
      return mPtr != NULL;
    }

    void swap (shared_ptr& rhs){
      T* tmpPtr = rhs.mPtr;
      long* tmpCounter = rhs.mCounter;
      rhs.mPtr = mPtr;
      rhs.mCounter =mCounter;
      mCounter = tmpCounter;
      mPtr = tmpPtr;
    }

  private:
    T *mPtr;
    long *mCounter;
  };

} // namespace trivial
