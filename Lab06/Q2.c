#include <stdio.h>
int main() {
    int num;
    printf("Enter your ticket number:");
    scanf("%d",&num);
    while (num>0) {
        printf("%d",num%10);
        num = num / 10;
    }
}