#include <stdio.h>
int main(){
    int n,i,j,val;
    printf("Enter number of elements: ");
    scanf("%d",&n);
    int arr[n];
    printf("Enter elements:\n");
    for(i=0;i<n;i++) scanf("%d",&arr[i]);
    printf("Enter value to delete: ");
    scanf("%d",&val);
    for(i=0;i<n;i++){
        if(arr[i]==val){
            for(j=i;j<n-1;j++) arr[j]=arr[j+1];
            n--; i--;
        }
    }
    printf("Array after deletion:\n");
    for(i=0;i<n;i++) printf("%d ",arr[i]);
    return 0;
}

