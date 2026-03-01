#include "runner.h"
#include "../kernel/hal/interrupts.h"
#include "types.h"
#include <cursor.h>
#include <logs.h>
#include <terminal.h>

static int count_tests(kernel_test_t *tests[MAX_TESTS]) {
  int s = 0;

  while (tests[s++] != NULL)
    ;

  return s - 1;
}

void run_tests(kernel_test_t *tests[MAX_TESTS]) {
  // tests should not be tampered with
  disable_cursor();
  disable_interrupts();

  const int n = count_tests(tests);

  // test stats
  int failed = 0;
  int successful = 0;

  msgf(STATUS_BLANK, "Starting %d test(s)...", n);

  for (int i = 0; i < n; i++) {
    msgf(STATUS_BLANK, "Running test \"%s\"...", tests[i]->name);
    const int res = tests[i]->run();
    msgf(STATUS_OK, "Ran test \"%s\" (exit code: %d)", tests[i]->name, res);

    if (res == 0) {
      successful++;
    } else {
      failed++;
    }
  }

  msgf(STATUS_OK, "Ran %d test(s), %d failed, %d successful", n, failed,
       successful);
}
