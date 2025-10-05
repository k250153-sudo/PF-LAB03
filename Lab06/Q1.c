
#include <stdio.h>

    int main() {
        int pin, sum = 0;

        printf("Enter a 4-digit PIN: ");
        scanf("%d", &pin);

        if (pin < 1000 || pin > 9999) {
            printf("Invalid PIN! Please enter a 4-digit number.\n");
            return 0;
        }


        while (pin > 0) {
            sum += pin % 10;
            pin /= 10;
        }

        if (sum > 10)
            printf("Strong PIN\n");
        else
            printf("Weak PIN\n");

        return 0;
    }


