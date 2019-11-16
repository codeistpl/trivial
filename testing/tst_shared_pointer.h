#pragma once

#include "ctordtormock.h"
#include <CppUTest/TestHarness.h>
#include <trivial/shared_ptr.h>

TEST_GROUP(shared_ptr){};

bool CtorDtorMock::dtor_triggered;

using namespace trivial;

TEST(shared_ptr, casts_to_true_is_have_managed_object) {
    shared_ptr<int> sp(1);
    CHECK_TRUE(bool(sp));
    CHECK_TRUE(1 == sp.use_count());
    CHECK_TRUE(1 == *sp.get());
    CHECK_TRUE(1 == *sp);
}

TEST(shared_ptr, parameterless_ctor_makes_ptr_without_ownership) {
    shared_ptr<int> sp;
    CHECK_TRUE(0 == sp.use_count());
    CHECK_FALSE(bool(sp));
}

TEST(shared_ptr, trivial_from_ptr_constructor) {
    shared_ptr<int> sp(new int(10));
    CHECK_TRUE(1 == sp.use_count());
    CHECK_TRUE(10 == *sp.get());
}

TEST(shared_ptr, assignment_replaces_namaged_object) {
    shared_ptr<int> sp = new int(10);
    CHECK_TRUE(bool(sp));
    CHECK_TRUE(1 == sp.use_count());
    CHECK_TRUE(10 == *sp);

    sp = new int(99);
    CHECK_TRUE(bool(sp));
    CHECK_TRUE(1 == sp.use_count());
    CHECK_TRUE(99 == *sp);
}

TEST(shared_ptr, CHECK_dtor_on_scope_exit) {

    CtorDtorMock *mock = new CtorDtorMock();
    {
        shared_ptr<CtorDtorMock> sptr(mock);
        CHECK_TRUE(1 == sptr.use_count());
        CHECK_TRUE(bool(sptr));
    }
    CHECK_TRUE(CtorDtorMock::dtor_triggered);
}

TEST(shared_ptr, shares_ownership_on_assigment) {

    shared_ptr<CtorDtorMock> inst1 = new CtorDtorMock();
    CHECK_TRUE(bool(inst1));
    CHECK_TRUE(1 == inst1.use_count());
    {
        shared_ptr<CtorDtorMock> inst2 = inst1;
        CHECK_TRUE(bool(inst2));
        CHECK_TRUE(2 == inst1.use_count());
        CHECK_TRUE(2 == inst2.use_count());
    }
    CHECK_TRUE(1 == inst1.use_count());
}

TEST(shared_ptr, shares_ownership_on_copy) {
    shared_ptr<CtorDtorMock> inst1 = new CtorDtorMock();
    CHECK_TRUE(bool(inst1));
    CHECK_TRUE(1 == inst1.use_count());
    {
        shared_ptr<CtorDtorMock> inst2(inst1);
        CHECK_TRUE(bool(inst2));
        CHECK_TRUE(2 == inst1.use_count());
        CHECK_TRUE(2 == inst2.use_count());
    }
    CHECK_TRUE(1 == inst1.use_count());
    CHECK_FALSE(CtorDtorMock::dtor_triggered);
}

TEST(shared_ptr, on_reset_decrement_counter) {
    shared_ptr<CtorDtorMock> inst1 = new CtorDtorMock();
    CHECK_TRUE(1 == inst1.use_count());

    shared_ptr<CtorDtorMock> inst2(inst1);
    CHECK_TRUE(2 == inst1.use_count());
    CHECK_TRUE(2 == inst2.use_count());
    inst2.reset();

    CHECK_FALSE(bool(inst2));
    CHECK_TRUE(0 == inst2.use_count());
    CHECK_TRUE(1 == inst1.use_count());
    CHECK_FALSE(CtorDtorMock::dtor_triggered);
}

TEST(shared_ptr, swap_ptrs) {
    shared_ptr<int> p1(99);
    shared_ptr<int> p2(11);
    shared_ptr<int> p21(p2);

    CHECK_TRUE(1 == p1.use_count());
    CHECK_TRUE(99 == *p1);
    CHECK_TRUE(2 == p2.use_count());
    CHECK_TRUE(11 == *p2);

    p1.swap(p2);

    CHECK_TRUE(1 == p2.use_count());
    CHECK_TRUE(99 == *p2);
    CHECK_TRUE(2 == p1.use_count());
    CHECK_TRUE(11 == *p1);
}
