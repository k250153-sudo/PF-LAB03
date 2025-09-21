#include <stdio.h>
#include <math.h>

int main() {
    int amount;
    float time,SI;
    double emi;
    char type[10];
    float IR = 0.12;
    printf("Enter the amount :");
    scanf("%d",&amount);
    printf("Enter the time(in years) :");
    scanf("%f",&time);
    float timeMonth = time *12;
    printf("which type of loan simple or compound:");
    scanf("%s",type);
    printf("The interest rate is assumed %.2f %% annually\n",(IR*100));
    switch(type[0]) {
        case 'S':
            case 's':
            SI = (amount*IR*time);
            emi = ((amount+SI)/timeMonth);
            printf
            ("Your EMI is %.2lf",emi);
            break;
        case 'C':
            case 'c':
            float r = IR/12;
            emi = (amount * r * pow(1+r,timeMonth)) / (pow(1+r,timeMonth) - 1);
            printf("Your EMI is %.2lf",emi);
            break;

    }


}