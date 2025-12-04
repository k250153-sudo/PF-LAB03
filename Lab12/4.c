#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Enter the number of movie categories: ");
    int n;
    scanf("%d",&n);
    int *rating =(int*)malloc(sizeof(int)*n);
    if (rating == NULL) {
        printf("Not enough space\n");
        return 1;
    }
    int total = 0;
    for (int i = 0; i < n; i++) {
        int rate=0;
        printf("Enter the ratings for category %d: ",i+1);
        scanf("%d",&rate);
        *(rating+i)=rate;
        total+=rate;
    }
    printf("Total ratings: %d",total);
    printf("Average rating: %.1f",(float)total/n);
    int heighest=rating[0], index=0;
    for (int i = 1; i < n; i++) {
        if (rating[i] > heighest) {
            heighest = rating[i];
            index = i;
        }
    }
    printf("Highest category is %d",index+1);
    printf("Enter the category you want to update: ");
    int category;
    scanf("%d",&category);
    int val;
    printf("Enter the new value: ");
    scanf("%d",&val);
    *(rating+(category-1))=val;
    printf("New category %d updated to %d",category,val);
    free(rating);
    return 0;
}