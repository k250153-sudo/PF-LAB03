#include <stdio.h>
#include <string.h>

#define MAX_ITEMS 100
#define MAX_LEN 50

struct Item {
    char name[MAX_LEN];
    char category[MAX_LEN];
    int quantity;
};

void filterByCategory(struct Item *inventory, int numItems, const char *category) {
    struct Item *ptr;
    printf("Items in category '%s':\n", category);
    for (ptr = inventory; ptr < inventory + numItems; ptr++) {
        if (strcmp(ptr->category, category) == 0) {
            printf("Name: %s, Quantity: %d\n", ptr->name, ptr->quantity);
        }
    }
}

void filterByMinQuantity(struct Item *inventory, int numItems, int minQty) {
    struct Item *ptr;
    printf("Items with quantity >= %d:\n", minQty);
    for (ptr = inventory; ptr < inventory + numItems; ptr++) {
        if (ptr->quantity >= minQty) {
            printf("Name: %s, Category: %s, Quantity: %d\n", ptr->name, ptr->category, ptr->quantity);
        }
    }
}

int main() {
    struct Item inventory[MAX_ITEMS];
    int numItems = 3;

    strcpy(inventory[0].name, "Laptop");
    strcpy(inventory[0].category, "Electronics");
    inventory[0].quantity = 5;

    strcpy(inventory[1].name, "Chair");
    strcpy(inventory[1].category, "Furniture");
    inventory[1].quantity = 10;

    strcpy(inventory[2].name, "Smartphone");
    strcpy(inventory[2].category, "Electronics");
    inventory[2].quantity = 8;

    // Filter demo
    filterByCategory(inventory, numItems, "Electronics");
    printf("\n");
    filterByMinQuantity(inventory, numItems, 7);

    return 0;
}
