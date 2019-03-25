#pragma once

#include "ctordtormock.h"
#include "trivial/shared_ptr.h"
#include <gmock/gmock-matchers.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace testing;
using namespace trivial;

TEST(shared_ptr, trivial_default_constructor) {
  shared_ptr<int> sp;
  EXPECT_EQ(0, sp.get());
}

TEST(shared_ptr, trivial_from_ptr_constructor) {
  shared_ptr<int> sp(new int(10));
  EXPECT_EQ(10, *sp.get());
}

TEST(shared_ptr, assignment) {
  shared_ptr<int> sp = new int(10);
  EXPECT_EQ(10, *sp.get());

  sp = new int(99);
  EXPECT_EQ(99, *sp.get());
}

TEST(shared_ptr, expect_dtor_on_scope_exit) {

  CtorDtorMock *mock = new CtorDtorMock();
  EXPECT_CALL(*mock, dtor());
  { shared_ptr<CtorDtorMock> sptr(mock); }
}

TEST(shared_ptr, expect_dtor_on_2_instance_reset) {

  shared_ptr<CtorDtorMock> inst1 = new CtorDtorMock();
  shared_ptr<CtorDtorMock> inst2 = inst1;
}
