#include <stdio.h>
void inputData(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("Enter number of patients for Day %d:",i+1);
        scanf("%d",&arr[i]);

    }
}
float averagePatients(int arr[], int n) {
    float average = 0,sum=0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    average = sum/n;
    printf("Average is %.2f\n",average);
    return 0;
}
int busiestDay(int arr[], int n) {
    int max = arr[0],min=arr[0];
    int max_c=0, min_c=0;
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
            max_c = i+1;
        }
        if (arr[i] < min) {
            min = arr[i];
            min_c = i+1;
        }
    }
    printf("Busiest Day: %d(%d patients)\n",max_c,max);
    printf("Slowest Day: %d(%d patients)\n",min_c,min);
    return 0;
}
int main() {
    int arr[7],n=7;
    inputData(arr,n);
    averagePatients(arr,n);
    busiestDay(arr,n);
return 0;

}