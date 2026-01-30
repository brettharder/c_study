#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "util.h"

#define ASSERT_TRUE(cond) do { \
    if (!(cond)) { \
        fprintf(stderr, "ASSERT_TRUE failed: %s (%s:%d)\n", #cond, __FILE__, __LINE__); \
        return 1; \
    } \
} while (0)

#define ASSERT_EQ_U64(a,b) do { \
    uint64_t _a=(a), _b=(b); \
    if (_a != _b) { \
        fprintf(stderr, "ASSERT_EQ_U64 failed: %llu != %llu (%s:%d)\n", \
                (unsigned long long)_a, (unsigned long long)_b, __FILE__, __LINE__); \
        return 1; \
    } \
} while (0)

static int test_strlen(void) {
    ASSERT_EQ_U64(util_strlen(""), 0);
    ASSERT_EQ_U64(util_strlen("a"), 1);
    ASSERT_EQ_U64(util_strlen("abc"), 3);

    // Cross-check against libc for a normal string
    const char *s = "quant-dev";
    ASSERT_EQ_U64(util_strlen(s), (uint64_t)strlen(s));
    return 0;
}

static int test_is_sorted(void) {
    int32_t a[] = {1, 2, 3};
    int32_t b[] = {3, 2, 1};
    ASSERT_TRUE(util_is_sorted_i32(a, 3) == 1);
    ASSERT_TRUE(util_is_sorted_i32(b, 3) == 0);
    return 0;
}

int main(void) {
    int rc = 0;
    rc |= test_strlen();
    rc |= test_is_sorted();

    if (rc == 0) {
        printf("ALL TESTS PASSED\n");
    }
    return rc;
}

