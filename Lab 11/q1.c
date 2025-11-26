#include <stdio.h>
#include <string.h>

struct Gift {
    char name[50];
    char type[50];
    int price;
    int quantity;
};

int main() {
    int p=0,q=0;
    printf("How many gifts do you want to enter: ");
    int i;
    scanf("%d",&i);
    getchar();
    struct Gift gift[i];
    for (int j=0;j<i;j++) {
        printf("Enter the name of gift %d: ",j+1);
        fgets(gift[j].name, sizeof(gift[j].name), stdin);
        gift[j].name[strcspn(gift[j].name, "\n")] = 0;
        printf("Enter the type of gift %d: ",j+1);
        fgets(gift[j].type, sizeof(gift[j].type), stdin);
        gift[j].type[strcspn(gift[j].type, "\n")] = 0;
        printf("Enter the price of gift %d: ",j+1);
        scanf("%d",&gift[j].price);
        printf("Enter the quantity of gift %d: ",j+1);
        scanf("%d",&gift[j].quantity);
        getchar();
    }
    printf("Enter the price threshold: ");
    int price_threshold;
    scanf("%d",&price_threshold);
    printf("Enter the quantity threshold");
    int quantity_threshold;
    scanf("%d",&quantity_threshold);
    for (int k=0;k<i;k++) {
        if (gift[k].quantity > quantity_threshold) {
            printf("%s has more quantity than %d\n",gift[k].name,quantity_threshold);
        }
        if (gift[k].price > price_threshold) {
            printf("%s has more price than %d\n",gift[k].name,price_threshold);
        }
    }
}
