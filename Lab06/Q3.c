#include <stdio.h>

int main() {
    int n, i, j, isPrime;

    printf("Enter a number: ");
    scanf("%d", &n);

    isPrime = 1;
    if (n <= 1)
        isPrime = 0;
    else {
        for (i = 2; i * i <= n; i++) {
            if (n % i == 0) {
                isPrime = 0;
                break;
            }
        }
    }

    if (isPrime)
        printf("%d is a Prime number.\n", n);
    else
        printf("%d is NOT a Prime number.\n", n);

    printf("Prime numbers between 1 and %d are:\n", n);
    for (i = 2; i < n; i++) {
        int primeFlag = 1;
        for (j = 2; j * j <= i; j++) {
            if (i % j == 0) {
                primeFlag = 0;
                break;
            }
        }
        if (primeFlag)
            printf("%d ", i);
    }

    return 0;
}
