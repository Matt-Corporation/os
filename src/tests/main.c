#include "main.h"
#include "runner.h"
#include "types.h"
#include <logs.h>
#include <panic.h>
#include <stddef.h>

int test() {
  msgf(STATUS_BLANK, "hello from test 1");
  return 0;
}

static kernel_test_t test1 = {
    .name = "test",
    .run = test,
};

static kernel_test_t panik = {
    .name = "PANIK!!1!",
    .run = (void *)__panicf,
};

void start_tests() {
  kernel_test_t *tests[MAX_TESTS] = {};

  DEFINE_TESTS(tests, &test1, &panik);
  run_tests(tests);
}
