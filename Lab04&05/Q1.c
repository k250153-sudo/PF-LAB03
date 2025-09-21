#include <stdio.h>

int main() {
    int a, b, c, second;

    // Input three numbers
    printf("Enter three integers: ");
    scanf("%d %d %d", &a, &b, &c);

    // Nested if-else logic
    if (a > b) {
        if (a > c) {
            // a is largest
            if (b > c)
                second = b;
            else
                second = c;
        } else {
            // c >= a > b
            second = a;
        }
    } else { // b >= a
        if (b > c) {
            // b is largest
            if (a > c)
                second = a;
            else
                second = c;
        } else {
            // c >= b >= a
            second = b;
        }
    }

    printf("The second largest number is: %d\n", second);

    return 0;
}