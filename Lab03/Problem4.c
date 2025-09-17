#include <stdio.h>
int main() {
    float BS, HRA, DA, GS;
    printf("Enter your salary: ");
    scanf("%f",&BS);
    HRA = 0.1*BS;
    DA = 0.05*BS;
    GS = BS + HRA + DA;
    printf("Your gross salary is %.2f",GS);
    return 0;


}