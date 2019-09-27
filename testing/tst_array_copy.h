#pragma once

#include "../trivial/array_copy.h"
#include <gtest/gtest.h>
#include <numeric>

using namespace trivial;

TEST(array_copy, simple_case) {
    int src[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int dst[10] = {0};

    copy_array(src, 10, dst, 10);
    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(dst[i], src[i]);
    }
}

TEST(array_copy, smaller_dst) {
    int src[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int dst[7] = {0};

    copy_array(src, 10, dst, 7);
    for (int i = 0; i < 7; i++) {
        EXPECT_EQ(dst[i], src[i]);
    }
}

TEST(array_copy, bigger_dst) {
    int src[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int dst[19] = {0};

    copy_array(src, 10, dst, 10);
    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(dst[i], src[i]);
    }
}
