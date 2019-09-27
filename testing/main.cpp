#include "tst_array.h"
#include "tst_array_copy.h"
#include "tst_optional.h"
#include "tst_shared_pointer.h"

#include <gtest/gtest.h>

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
