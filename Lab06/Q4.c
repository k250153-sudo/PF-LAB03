#include <stdio.h>
int main() {
    int i=0;
    float marks,sum=0,avg=0;
    printf("Enter the marks: ");
    scanf("%f",&marks);
    while (marks != -1) {
        sum += marks;
        printf("Enter the marks: ");
        scanf("%f",&marks);
        i++;
    }
    avg = sum/i;
    printf("%.2f",avg);

}