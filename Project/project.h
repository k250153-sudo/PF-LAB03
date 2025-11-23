#ifndef PROJECT_H
#define PROJECT_H

#include <time.h>

#define MAX_ITEMS 100
#define MAX_NAME_LENGTH 50
#define MAX_ROLL_LENGTH 9
#define MAX_ROOM_LENGTH 20

// Shop and menu data
extern char shops[3][50];
extern char menu1[5][50];
extern int price1[5];
extern char menu2[5][50];
extern int price2[5];
extern char menu3[5][50];
extern int price3[5];

// Order data structure
typedef struct {
    char name[MAX_NAME_LENGTH];
    char roll[MAX_ROLL_LENGTH];
    char room[MAX_ROOM_LENGTH];
    char items[MAX_ITEMS][50];
    int prices[MAX_ITEMS];
    int itemCount;
    int subtotal;
    int deliveryFee;
    int discount;
    int total;
} Order;

// Function declarations
void initializeShopsAndMenus();
int isValidRoll(const char* roll);
int isValidRoom(const char* room);
int calculateSubtotal(Order* order);
int calculateDiscount(int subtotal);
int calculateTotal(Order* order);
void addItemToOrder(Order* order, int shop, int itemIndex);
void removeItemFromOrder(Order* order, int index);
void clearOrder(Order* order);
void saveOrderToFile(Order* order);
void cancelOrderByRoll(const char* roll, char* resultMessage);
void getOrderStatus(const char* roll, char* resultMessage);

#endif // PROJECT_H