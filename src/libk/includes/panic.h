#pragma once

void __panicf(const char *format, ...);

#define panicf(args...)                                                        \
  __panicf(args);                                                              \
  __builtin_unreachable()
