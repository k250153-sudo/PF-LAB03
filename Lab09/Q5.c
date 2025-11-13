#include <stdio.h>
void analyzeData(int *arr, int n, int *max, int *min, float *avg) {
    *max=arr[0];
    *min=arr[0];
    int sum=arr[0];
    for(int i=1; i<n; i++) {
        if(arr[i]>*max) {
            *max=arr[i];
        }
        if(arr[i]<*min) {
            *min=arr[i];
        }
        sum+=arr[i];
    }
    *avg=(float)(sum)/n;
}
int main() {
    int n,max,min;
    float avg;
    printf("Enter number of elements: ");
    scanf("%d",&n);
    int arr[n];
    for (int i=0;i<n;i++) {
        printf("Enter element %d: ",i);
        scanf("%d",&arr[i]);
    }
    analyzeData(arr,n,&max,&min,&avg);
    printf("Maximum = %d\n",max);
    printf("Minimum = %d\n",min);
    printf("Average = %.2f",avg);
    return 0;
}