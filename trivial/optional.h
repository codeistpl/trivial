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
#include <stdexcept>

/*!
 * \addtogroup trivial
 * This is a set of trivialized implementations of common elementals availiable
 * in c11 and later. Before using this, please consider using c++ standard that
 * already implemented this, or use other 3rd party widely used library that
 * implemented this (for example boost)
 */
namespace trivial {

/*!
 * \brief The bad_optional_access exception
 */
class bad_optional_access : public std::logic_error {
public:
  bad_optional_access() : std::logic_error("accesing optional with no value"){};
};

/*!
 * \brief The optional class is a trivialized implementaion of std::optional
 */
template <typename T> class optional {
public:
  optional() = default;
  optional(T v) {
    mValue = v;
    opt = true;
  }

  constexpr optional<T> &operator=(const T &rhs) {
    mValue = rhs;
    opt = rhs;
    return *this;
  }

  constexpr T &operator*() & {
    if (!opt) {
      throw bad_optional_access();
    }

    return mValue;
  }

  constexpr const T &operator*() const & {
    if (!opt) {
      throw bad_optional_access();
    }
    return mValue;
  }

  constexpr T *operator->() {
    if (!opt) {
      throw bad_optional_access();
    }
    return &mValue;
  }

  constexpr const T *operator->() const {
    if (!opt) {
      throw bad_optional_access();
    }
    return &mValue;
  }

  inline const T &value() const {
    if (!opt) {
      throw bad_optional_access();
    }
    return mValue;
  }

  constexpr bool has_value() { return opt; }

  constexpr explicit operator bool() const { return opt; }

  void reset() { opt = false; }

private:
  T mValue;
  bool opt = false;
};

template <typename T>
inline bool operator==(const T &lhs, const optional<T> &rhs) {
  return (lhs == rhs.value());
}

template <typename T>
inline bool operator==(const optional<T> &lhs, const T &rhs) {
  return (rhs == lhs.value());
}

template <typename T>
inline bool operator!=(const T &lhs, const optional<T> &rhs) {
  return !(lhs == rhs);
}

template <typename T>
inline bool operator!=(const optional<T> &lhs, const T &rhs) {
  return !(rhs == lhs);
}

template <typename T>
inline bool operator==(const optional<T> &lhs, const optional<T> &rhs) {
  return (lhs.value() == rhs.value());
}

template <typename T>
inline bool operator!=(const optional<T> &lhs, const optional<T> &rhs) {
  return !(lhs == rhs);
}

template <typename T>
inline bool operator>=(const optional<T> &lhs, const optional<T> &rhs) {
  return lhs.value() >= rhs.value();
}

template <typename T>
inline bool operator>=(const optional<T> &lhs, const T &rhs) {
  return lhs.value() >= rhs;
}

template <typename T>
inline bool operator>=(const T &lhs, const optional<T> &rhs) {
  return lhs >= rhs.value();
}

template <typename T>
inline bool operator<=(const optional<T> &lhs, const optional<T> &rhs) {
  return lhs.value() <= rhs.value();
}

template <typename T>
inline bool operator<=(const optional<T> &lhs, const T &rhs) {
  return lhs.value() <= rhs;
}

template <typename T>
inline bool operator<=(const T &lhs, const optional<T> &rhs) {
  return lhs <= rhs.value();
}

template <typename T>
inline bool operator>(const optional<T> &rhs, const optional<T> &lhs) {
  return rhs.value() > lhs.value();
}

template <typename T>
inline bool operator>(const optional<T> &rhs, const T &lhs) {
  return rhs.value() > lhs;
}

template <typename T>
inline bool operator>(const T &rhs, const optional<T> &lhs) {
  return rhs > lhs.value();
}

template <typename T>
inline bool operator<(const optional<T> &rhs, const optional<T> &lhs) {
  return rhs.value() < lhs.value();
}

template <typename T>
inline bool operator<(const T &rhs, const optional<T> &lhs) {
  return rhs < lhs.value();
}

template <typename T>
inline bool operator<(const optional<T> &rhs, const T &lhs) {
  return rhs.value() < lhs;
}

} // namespace trivial
