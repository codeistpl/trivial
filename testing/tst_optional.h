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

#include "trivial/optional.h"
#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>
#include <memory>

using namespace testing;

struct S {
    int getFour() const { return 4; }
};

TEST(optional, construction) {
    trivial::optional<int> zero(0);
    EXPECT_TRUE(zero.has_value());
    EXPECT_EQ(0, zero);
    trivial::optional<int> opt;
    EXPECT_FALSE(opt.has_value());
}

TEST(optional, assignment) {
    trivial::optional<int> opt = 0;
    EXPECT_EQ(opt, 0);
    opt = 10;
    EXPECT_EQ(opt, 10);

    auto opt2 = opt;
    EXPECT_EQ(opt2, 10);
    EXPECT_EQ(opt, opt2);
}

TEST(optional, getters) {
    trivial::optional<int> opt = 10;
    EXPECT_EQ(opt, 10);
    const int &constRef = *opt;
    EXPECT_EQ(constRef, 10);
    int &ref = *opt;
    EXPECT_EQ(ref, 10);

    int val = opt.value();
    EXPECT_EQ(val, 10);
    const int constVal = opt.value();
    EXPECT_EQ(constVal, 10);

    trivial::optional<S> opt2 = S{};
    EXPECT_EQ(opt2->getFour(), 4);
}

TEST(optional, comparision) {
    trivial::optional<int> opt = 10;
    trivial::optional<int> opt2 = opt;
    trivial::optional<int> opt3 = 99;

    EXPECT_EQ(opt, opt2);
    EXPECT_EQ(opt, 10);
    EXPECT_EQ(10, opt);

    EXPECT_NE(opt, opt3);
    EXPECT_NE(opt, 99);
    EXPECT_NE(99, opt);

    EXPECT_GT(opt3, opt2);
    EXPECT_GT(99, opt2);
    EXPECT_GT(opt3, 10);

    EXPECT_LT(opt2, opt3);
    EXPECT_LT(10, opt3);
    EXPECT_LT(opt, 99);

    EXPECT_GE(opt, opt2);
    EXPECT_GE(opt3, opt);
    EXPECT_GE(opt, 10);
    EXPECT_GE(10, opt);
    EXPECT_GE(opt3, 10);

    EXPECT_LE(opt, opt2);
    EXPECT_LE(opt2, opt3);
    EXPECT_LE(opt, 99);
    EXPECT_LE(10, opt3);
}

TEST(optional, reset) {
    trivial::optional<int> opt;
    EXPECT_FALSE(opt.has_value());
    opt = 10;
    EXPECT_TRUE(opt.has_value());
    opt.reset();
    EXPECT_FALSE(opt.has_value());
}

TEST(optional, bad_access) {
    trivial::optional<int> opt;
    EXPECT_THROW(opt.value(), trivial::bad_optional_access);
    EXPECT_THROW({ opt == 10; }, trivial::bad_optional_access);
    EXPECT_THROW({ *opt == 10; }, trivial::bad_optional_access);
}
