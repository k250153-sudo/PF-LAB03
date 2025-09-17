#include <stdio.h>

int main() {
    float num1, num2, num3, sum, percentage;
    printf("Enter marks of the first subject:\n");
    scanf("%f", &num1);
    printf("Enter marks of the second subject:\n");
    scanf("%f", &num2);
    printf("Enter marks of the third subject:\n");
    scanf("%f", &num3);
    sum = num1 + num2 + num3;
    percentage = (sum / 3);
    printf("The total marks are: %.2f\n",sum);
    printf("Percentage is :%.2f\n",percentage);
    return 0;

}