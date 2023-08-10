#pragma once

#include <stdbool.h>
#include <sys/types.h>

typedef union {
  void *as_ptr;
  double as_double;
  float as_float;
  int as_int;
  uint as_uint;
  bool as_bool;
  char as_char;
} Value64;
