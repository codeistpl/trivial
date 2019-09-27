#pragma once

#include "ctordtormock.h"
#include "trivial/shared_ptr.h"
#include <gmock/gmock-matchers.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace testing;
using namespace trivial;

TEST(shared_ptr, casts_to_true_is_have_managed_object) {
    shared_ptr<int> sp(1);
    EXPECT_TRUE(sp);
    EXPECT_EQ(1, sp.use_count());
    EXPECT_EQ(1, *sp.get());
    EXPECT_EQ(1, *sp);
}

TEST(shared_ptr, parameterless_ctor_makes_ptr_without_ownership) {
    shared_ptr<int> sp;
    EXPECT_EQ(0, sp.use_count());
    EXPECT_FALSE(sp);
}

TEST(shared_ptr, trivial_from_ptr_constructor) {
    shared_ptr<int> sp(new int(10));
    EXPECT_EQ(1, sp.use_count());
    EXPECT_EQ(10, *sp.get());
}

TEST(shared_ptr, assignment_replaces_namaged_object) {
    shared_ptr<int> sp = new int(10);
    EXPECT_TRUE(sp);
    EXPECT_EQ(1, sp.use_count());
    EXPECT_EQ(10, *sp);

    sp = new int(99);
    EXPECT_TRUE(sp);
    EXPECT_EQ(1, sp.use_count());
    EXPECT_EQ(99, *sp);
}

TEST(shared_ptr, expect_dtor_on_scope_exit) {
    CtorDtorMock *mock = new CtorDtorMock();
    EXPECT_CALL(*mock, dtor());
    {
        shared_ptr<CtorDtorMock> sptr(mock);
        EXPECT_EQ(1, sptr.use_count());
        EXPECT_TRUE(sptr);
    }
}

TEST(shared_ptr, shares_ownership_on_assigment) {
    shared_ptr<CtorDtorMock> inst1 = new CtorDtorMock();
    EXPECT_TRUE(inst1);
    EXPECT_EQ(1, inst1.use_count());
    EXPECT_CALL(*inst1, dtor());
    {
        shared_ptr<CtorDtorMock> inst2 = inst1;
        EXPECT_TRUE(inst2);
        EXPECT_EQ(2, inst1.use_count());
        EXPECT_EQ(2, inst2.use_count());
    }
    EXPECT_EQ(1, inst1.use_count());
}

TEST(shared_ptr, shares_ownership_on_copy) {
    shared_ptr<CtorDtorMock> inst1 = new CtorDtorMock();
    EXPECT_TRUE(inst1);
    EXPECT_EQ(1, inst1.use_count());
    EXPECT_CALL(*inst1, dtor());
    {
        shared_ptr<CtorDtorMock> inst2(inst1);
        EXPECT_TRUE(inst2);
        EXPECT_EQ(2, inst1.use_count());
        EXPECT_EQ(2, inst2.use_count());
    }
    EXPECT_EQ(1, inst1.use_count());
}

TEST(shared_ptr, on_reset_decrement_counter) {
    shared_ptr<CtorDtorMock> inst1 = new CtorDtorMock();
    EXPECT_EQ(1, inst1.use_count());
    EXPECT_CALL(*inst1, dtor());

    shared_ptr<CtorDtorMock> inst2(inst1);
    EXPECT_EQ(2, inst1.use_count());
    EXPECT_EQ(2, inst2.use_count());
    inst2.reset();

    EXPECT_FALSE(inst2);
    EXPECT_EQ(0, inst2.use_count());
    EXPECT_EQ(1, inst1.use_count());
}

TEST(shared_ptr, swap_ptrs) {
    shared_ptr<int> p1(99);
    shared_ptr<int> p2(11);
    shared_ptr<int> p21(p2);

    EXPECT_EQ(1, p1.use_count());
    EXPECT_EQ(99, *p1);
    EXPECT_EQ(2, p2.use_count());
    EXPECT_EQ(11, *p2);

    p1.swap(p2);

    EXPECT_EQ(1, p2.use_count());
    EXPECT_EQ(99, *p2);
    EXPECT_EQ(2, p1.use_count());
    EXPECT_EQ(11, *p1);
}
