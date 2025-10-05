#include <stdio.h>
int main() {
    int num,even=0,odd=0,check;
    printf("Enter a number:");
    scanf("%d",&num);
    while (num>0) {
        check = num %10;
        num = num / 10;
        if (check % 2 == 0) {
            even ++;
        }
        else {
            odd++;
        }

    }
    printf("The number of odd digits are %d and even %d",odd,even);
}