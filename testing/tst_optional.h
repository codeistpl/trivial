/*
 MIT License
 Copyright (c) [2018] [Michal Sopniewski]

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
*/

#pragma once

#include "trivial/optional.h"
#include <CppUTest/TestHarness.h>

// using namespace testing;

struct S {
    int getFour() const { return 4; }
};

TEST_GROUP(optional){};

TEST(optional, construction) {

    trivial::optional<int> zero(0);
    CHECK(zero.has_value());
    CHECK_TRUE(0 == zero);
    trivial::optional<int> opt;
    CHECK_FALSE(opt.has_value());
}

TEST(optional, assignment) {
    trivial::optional<int> opt = 0;
    CHECK_TRUE(opt == 0);
    opt = 10;
    CHECK_TRUE(opt == 10);

    trivial::optional<int> opt2 = opt;
    CHECK_TRUE(opt2 == 10);
    CHECK_TRUE(opt == opt2);
}

TEST(optional, getters) {
    trivial::optional<int> opt = 10;
    CHECK_TRUE(opt == 10);
    const int &constRef = *opt;
    CHECK_TRUE(constRef == 10);
    int &ref = *opt;
    CHECK_TRUE(ref == 10);

    int val = opt.value();
    CHECK_TRUE(val == 10);
    const int constVal = opt.value();
    CHECK_TRUE(constVal == 10);

    trivial::optional<S> opt2 = S();
    CHECK_TRUE(opt2->getFour() == 4);
}

TEST(optional, comparision) {
    trivial::optional<int> opt = 10;
    trivial::optional<int> opt2 = opt;
    trivial::optional<int> opt3 = 99;

    CHECK_TRUE(opt == opt2);
    CHECK_TRUE(opt == 10);
    CHECK_TRUE(10 == opt);

    CHECK_FALSE(opt == opt3);
    CHECK_FALSE(opt == 99);
    CHECK_FALSE(99 == opt);

    CHECK_TRUE(opt3 > opt2);
    CHECK_TRUE(99 > opt2);
    CHECK_TRUE(opt3 > 10);

    CHECK_TRUE(opt2 < opt3);
    CHECK_TRUE(10 < opt3);
    CHECK_TRUE(opt < 99);

    CHECK_TRUE(opt >= opt2);
    CHECK_TRUE(opt3 >= opt);
    CHECK_TRUE(opt >= 10);
    CHECK_TRUE(10 >= opt);
    CHECK_TRUE(opt3 >= 10);

    CHECK_TRUE(opt <= opt2);
    CHECK_TRUE(opt2 <= opt3);
    CHECK_TRUE(opt <= 99);
    CHECK_TRUE(10 <= opt3);
}

TEST(optional, reset) {
    trivial::optional<int> opt;
    CHECK_FALSE(opt.has_value());
    opt = 10;
    CHECK_TRUE(opt.has_value());
    opt.reset();
    CHECK_FALSE(opt.has_value());
}

TEST(optional, bad_access) {
    trivial::optional<int> opt;

    bool catches[3] = {false};
    try {
        int x = opt.value();
    } catch (trivial::bad_optional_access &) {
        catches[0] = true;
    }

    try {
        opt == 10;
    } catch (trivial::bad_optional_access &) {
        catches[1] = true;
    }

    try {
        *opt == 10;
    } catch (trivial::bad_optional_access &) {
        catches[2] = true;
    }

    for (int i = 0; i < sizeof(catches); i++) {
        CHECK_TRUE(catches[i]);
    }
}
