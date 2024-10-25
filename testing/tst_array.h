// #include "../trivial/array.h"
// #include <gtest/gtest.h>

// using namespace testing;
// using namespace trivial;

// TEST(array, ctor) {
//    array<int, 10> a;
//    EXPECT_EQ(size_t(10), a.size());
//}

// TEST(array, access) {
//    array<int, 10> a;

//    for (size_t i = 0; i < a.size(); i++) {
//        a[i] = static_cast<int>(a.size() - i);
//        EXPECT_EQ(size_t(a.size()) - i, a[i]);
//    }

//    for (size_t i = 0; i < a.size(); i++) {
//        a.at(i) = static_cast<int>(i);
//        EXPECT_EQ(i, a[i]);
//    }

//    EXPECT_THROW(a.at(a.size() + 1), std::out_of_range);
//}

// TEST(array, copy) {
//    array<int, 30> a;
//    for (size_t i = 0; i < a.size(); i++) {
//        a[i] = static_cast<int>(a.size() - i);
//        EXPECT_EQ(size_t(a.size()) - i, a[i]);
//    }

//    array<int, 30> b = a;
//    for (size_t i = 0; i < a.size(); i++) {
//        EXPECT_EQ(size_t(b.size()) - i, b[i]);
//    }
//}
