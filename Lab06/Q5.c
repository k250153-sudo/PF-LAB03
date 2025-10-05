#include <math.h>
#include <stdio.h>
int main() {
    int num;
    printf("Enter a number:");
    scanf("%d",&num);
    if (num == 0 || num == 1) {
        printf("1");
    }
    else {
        for (int i = num-1;i>=1;i--) {
            num = num * i;

        }
        printf("%d",num);
    }
    return 0;

}