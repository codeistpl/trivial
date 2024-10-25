#pragma once

#include "ctordtormock.h"
#include <CppUTest/TestHarness.h>
#include <trivial/unique_ptr.h>

TEST_GROUP(unique_ptr){};

using namespace trivial;

TEST(unique_ptr, casts_to_true_is_have_managed_object) {
    unique_ptr<int> up(new int(1));
    CHECK_TRUE(bool(up));
    CHECK_TRUE(1 == *up.get());
    CHECK_TRUE(1 == *up);
}

TEST(unique_ptr, parameterless_ctor_makes_ptr_without_ownership) {
    unique_ptr<int> up;
    CHECK_FALSE(bool(up));
}

TEST(unique_ptr, trivial_from_ptr_constructor) {

    unique_ptr<int> up;
    up = new int(10);

    CHECK_TRUE(10 == *up.get());
}