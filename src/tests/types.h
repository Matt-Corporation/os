#pragma once

typedef struct kernel_test {
  char *name;
  int (*run)();
} kernel_test_t;

// Disclaimer: this code was improved by ChatGPT.
#define DEFINE_TESTS(dst, ...)                                                 \
  do {                                                                         \
                                                                               \
    kernel_test_t *const _src[MAX_TESTS] = {__VA_ARGS__, NULL};                \
    size_t _i = 0;                                                             \
                                                                               \
    while (_src[_i] && _src[_i]->name) {                                       \
      (dst)[_i] = _src[_i];                                                    \
      _i++;                                                                    \
    }                                                                          \
                                                                               \
    (dst)[_i] = NULL;                                                          \
  } while (0)
