#include <stdio.h>

void inputdata(int arr[],int n) {
    for (int i = 0; i < n; i++) {
        printf("Enter vehicle count for road %d:",i+1);
        scanf("%d",&arr[i]);
    }
}
int readtarget(){
    int target;
    printf("Enter target vehicle count:");
    scanf("%d",&target);
    return target;
}
void roadnumbers(int arr[],int n,int *r1,int *r2,int target) {

    for(int i=0;i<n;i++) {
        for(int j=i+1;j<n;j++) {
            if ((arr[i]+arr[j])==target) {
                *r1=i+1;
                *r2=j+1;
                return;
            }
        }
    }
}
int main() {
    printf("Enter the number of roads:");
    int n;
    scanf("%d",&n);
    int arr[n];
    inputdata(arr,n);
    int r1,r2;
    int target=readtarget();
    roadnumbers(arr,n,&r1,&r2,target);
    printf("The two roads are %d and %d",r1,r2);
    return 0;
}

