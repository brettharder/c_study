#include "pointers.h"
#include <stdio.h>

// For now, just a stub that prints and returns
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void multiply_two_numbers(int *a, int *b) {
    *a = *a * *b;
}

void pointers_demo(void) {
    int x = 10;
    int y = 20;
    
    printf("Before: x=%d, y=%d\n", x, y);
    swap(&x, &y);  // Pass addresses with &
    printf("After:  x=%d, y=%d\n", x, y);

    printf("Before: x=%d\n", x);
    multiply_two_numbers(&x, &y);
    printf("After:  x=%d\n", x);
}
