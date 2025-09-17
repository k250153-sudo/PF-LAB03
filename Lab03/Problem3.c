#include <stdio.h>
int main() {
    int num;
    printf("Enter a number between 65 and 90 :");
    scanf("%d",&num);
    while (num<65 || num>90) {
        printf("Number is outside the range.The correct range is from 65 to 90.\nEnter the number again:");
        scanf("%d",&num);
    }
    printf("The ASCII value of the number %d is %c ",num,num);
    return 0;

}