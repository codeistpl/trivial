#include "tst_array.h"
#include "tst_array_copy.h"
#include "tst_optional.h"
#include "tst_shared_pointer.h"
#include "tst_unique_pointer.h"
#include "tst_weak_pointer.h"

#include <CppUTest/CommandLineTestRunner.h>

int main(int argc, char *argv[]) {
    return CommandLineTestRunner::RunAllTests(argc, argv);
}
