#include <stdio.h>
int main() {
    int value;
    printf("Please enter a value in the range 1...7: ");
    scanf("%d", &value);

    switch (value) {
        case 1:
            printf("You entered Monday\n");
            break;
        case 2:
            printf("You entered Tuesday\n");
            break;
        case 3:
            printf("You entered Wednesday\n");
            break;
        case 4:
            printf("You entered Thursday\n");
            break;
        case 5:
            printf("You entered Friday\n");
            break;
        case 6:
            printf("You entered Saturday\n");
            break;
        case 7:
            printf("You entered Sunday\n");
            break;
        default:
            printf("Invalid input, enter a value between 1 and 7.\n");
    }
    return 0;
}
