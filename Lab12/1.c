#include <stdio.h>
#include <stdlib.h>
int main() {
    printf("Enter the number of vook categories: ");
    int n;
    scanf("%d",&n);
    int *stock=(int *)malloc(n*(sizeof(int)));
    if (stock==NULL) {
        printf("Memory Error");
        return 1;
    }
    int total=0,min=0;
    for (int i=0;i<n;i++) {
        printf("Enter the stock for category number %d: ",i+1);
        scanf("%d",&stock[i]);
        total+=stock[i];
    }
    min=*stock;
    int index=0;
    for (int i=1;i<n;i++) {
        if (stock[i]<min) {
            min=stock[i];
            index=i;
        }
    }
    printf("Total stock is: %d\n",total);
    printf("Average stock is: %.1f\n",(float)total/n);
    printf("The category index of lowest stock is %d",index+1);
    free(stock);
    int updateIndex;
    printf("Enter the category to update: ");
    scanf("%d", &updateIndex);

    int val;
    printf("Enter the value: ");
    scanf("%d", &val);

    stock[updateIndex - 1] = val;
    return 0;
}
