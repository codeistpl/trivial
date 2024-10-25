#pragma once

#include "ctordtormock.h"
#include <CppUTest/TestHarness.h>
#include <CppUTest/UtestMacros.h>
#include <trivial/weak_ptr.h>

using namespace trivial;
TEST_GROUP(weak_ptr){};

TEST(weak_ptr, parameterless_ctor_makes_ptr_without_ownership) {
    weak_ptr<int> wp;
    CHECK_FALSE(bool(wp.lock()));
}

TEST(weak_ptr, trivial_from_shared_ptr_constructor) {
    shared_ptr<int> sp(new int(10));
    weak_ptr<int> wp(sp);
    CHECK_TRUE(bool(*wp.lock()));
    CHECK_TRUE(10 == *wp.lock());
}

TEST(weak_ptr, trivial_from_shared_ptr_constructor_and_dtor) {
    shared_ptr<int> sp(new int(10));
    weak_ptr<int> wp(sp);
    CHECK_EQUAL(1, sp.use_count());
    sp.reset();
    CHECK_FALSE(bool(sp));
    // CHECK_FALSE(bool(wp.lock()));
}