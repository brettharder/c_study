#include "util.h"

#include <time.h>

size_t util_strlen(const char *s) {
    // Intentionally simple; you'll explore UB around null pointers later.
    size_t n = 0;
    while (s[n] != '\0') {
        n++;
    }
    return n;
}

int util_is_sorted_i32(const int32_t *a, size_t n) {
    if (n < 2) return 1;
    for (size_t i = 1; i < n; i++) {
        if (a[i - 1] > a[i]) return 0;
    }
    return 1;
}

uint64_t util_now_ns(void) {
    // macOS: clock_gettime is available on modern macOS.
    // If yours errors, tell me the exact error and I'll give a mach_absolute_time version.
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)ts.tv_sec * 1000000000ull + (uint64_t)ts.tv_nsec;
}

