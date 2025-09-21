#include <stdio.h>
int main() {
    int units;
    float bill;
    printf("Enter number of units : ");
    scanf("%d",&units);
    if (units > 300) {
        bill = (units-300) * 15;
        bill = bill + (100*5) + (100*7) + (100*10);
    }
    else {
        if (units < 300 && units >= 200) {
            bill = (units-200) * 10;
            bill = bill + (100*5) + (100*7);
        }
        else {
            if (units < 200 && units >= 100) {
                bill = (units-100) * 7;
                bill = bill + (100*5);
            }
            else {
                bill = units * 5;
            }
        }
    }
    printf("The bill is %.2f",bill);
    return 0;
}