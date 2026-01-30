#ifndef UTIL_H
#define UTIL_H

#include <stddef.h>
#include <stdint.h>

// Safe-ish helpers for early learning (you'll expand these)
size_t  util_strlen(const char *s);
int     util_is_sorted_i32(const int32_t *a, size_t n);

// Simple timing helper for benches (nanoseconds)
uint64_t util_now_ns(void);

#endif // UTIL_H

