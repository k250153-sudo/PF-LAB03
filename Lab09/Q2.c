#include <stdio.h>

float bonuscalc(float sal) {
    if (sal<30000) {
        sal = sal*0.2;
    }
    else {
        sal = sal*0.1;
    }

    return sal;
}
int main() {

    float sum=0 ;
    float sal[5]={0};
    float bonus[5]={0};
    for (int i=0;i<5;i++) {
        printf("Enter the salary of Employee %d",i+1);
        scanf("%f",&sal[i]);
        bonus[i]=bonuscalc(sal[i]);
    }
    for (int i=0;i<5;i++) {
        printf("Employee %d Bonus: %.2f",i+1,bonus[i]);
        sum =sum +sal[i]+bonus[i] ;
    }
    printf("Total Payout is %.2f",sum);
}

