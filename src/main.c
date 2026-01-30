#include <stdio.h>
#include <stdint.h>

#include "util.h"
#include "pointers.h"  // <-- Include the header to get function declarations

int main(void) {
    // Original template code
    const char *msg = "Hello, C project template!";
    printf("%s (len=%zu)\n", msg, util_strlen(msg));

    int32_t a[] = {1, 2, 2, 5, 9};
    printf("sorted? %s\n", util_is_sorted_i32(a, sizeof(a)/sizeof(a[0])) ? "yes" : "no");

    printf("\n");  // Blank line separator
    
    // Call our pointers demo
    pointers_demo();  // <-- This calls the function defined in pointers.c

    return 0;
}
