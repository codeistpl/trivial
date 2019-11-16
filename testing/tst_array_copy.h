#pragma once

#include <CppUTest/TestHarness.h>
#include <numeric>
#include <trivial/array_copy.h>

using namespace trivial;

TEST_GROUP(array_copy){};

TEST(array_copy, simple_case) {
    int src[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int dst[10] = {0};

    copy_array(src, 10, dst, 10);
    for (int i = 0; i < 10; i++) {
        CHECK_TRUE(dst[i] == src[i]);
    }
}

TEST(array_copy, smaller_dst) {
    int src[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int dst[7] = {0};

    copy_array(src, 10, dst, 7);
    for (int i = 0; i < 7; i++) {
        CHECK_TRUE(dst[i] == src[i]);
    }
}

TEST(array_copy, bigger_dst) {
    int src[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int dst[19] = {0};

    copy_array(src, 10, dst, 10);
    for (int i = 0; i < 10; i++) {
        CHECK_TRUE(dst[i] == src[i]);
    }
}
