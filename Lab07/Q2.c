# include <stdio.h>

int main() {
    float power[24];
    float sum=0,avg = 0;
    for (int i =0 ; i<24;i++) {
        printf("Enter the power for hour %d: ",i);
        scanf("%f",&power[i]);
        sum+=power[i];

    }
    avg = sum/24;
    printf("average is %.2f\n",avg);
    printf("Sum is %.2f",sum);
    return 0;
}