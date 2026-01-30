#include <stdio.h>
#include <stdint.h>

#include "util.h"

int main(void) {
    const char *s = "this is a moderately long string used for benchmarking strlen-ish loops";

    // Warm-up
    volatile size_t sink = 0;
    for (int i = 0; i < 10000; i++) {
        sink ^= util_strlen(s);
    }

    const int iters = 2000000;
    uint64_t t0 = util_now_ns();
    for (int i = 0; i < iters; i++) {
        sink ^= util_strlen(s);
    }
    uint64_t t1 = util_now_ns();

    double ns_per = (double)(t1 - t0) / (double)iters;
    printf("util_strlen: %.2f ns/op (sink=%zu)\n", ns_per, (size_t)sink);

    return 0;
}

