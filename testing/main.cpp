#include "tst_optional.h"
#include "tst_shared_pointer.h"
#include "tst_array_copy.h"

#include <gtest/gtest.h>

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
