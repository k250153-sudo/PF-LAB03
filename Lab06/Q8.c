#include <stdio.h>
int main() {
    int n,n_2,np1,c;
    printf("Enter a number:");
    scanf("%d",&n);
    n_2=n*2;
    np1=n+1;
    if (n_2 == 0 || n_2 == 1) {
        n_2=1;
    }
    else {
        for (int i = n_2-1;i>=1;i--) {
            n_2 = n_2 * i;

        }
    }
    if (np1 == 0 || np1 == 1) {
        np1 =1;
    }
    else {
        for (int i = np1-1;i>=1;i--) {
            np1 = np1 * i;

        }
    }
    if (n == 0 || n == 1) {
        n=1;
    }
    else {
        for (int i = n-1;i>=1;i--) {
            n = n * i;

        }
    }
    c=(n_2/(n*np1));
    printf("The catalan term is %d",c);


}