#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_ITEMS 100

char shops[3][50] = {"FAST Canteen", "CS Block Snacks", "Main Gate Juice Bar"};

char menu1[5][50] = {"Burger", "Fries", "Zinger", "Roll", "Drink"};
int price1[5] = {200, 100, 250, 120, 80};

char menu2[5][50] = {"Patties", "Sandwich", "Chips", "Cup Cake", "Tea"};
int price2[5] = {40, 120, 50, 70, 30};

char menu3[5][50] = {"Mango Shake", "Strawberry Shake", "Oreo Shake", "Cold Coffee", "Water"};
int price3[5] = {150, 180, 200, 160, 40};

char selectedItems[MAX_ITEMS][50];
int selectedPrices[MAX_ITEMS];
int count = 0;

int selectShop() {
    int c;
    printf("\nSelect Shop:\n");
    printf("1. %s\n", shops[0]);
    printf("2. %s\n", shops[1]);
    printf("3. %s\n", shops[2]);
    printf("4. Finish Ordering\n");
    scanf("%d", &c);
    return c;
}

void showMenu(int shop) {
    int i;
    if(shop == 1){
        for(i=0;i<5;i++){
            printf("%d. %s - %d\n", i+1, menu1[i], price1[i]);
        }
    } else if(shop == 2){
        for(i=0;i<5;i++){
            printf("%d. %s - %d\n", i+1, menu2[i], price2[i]);
        }
    } else if(shop == 3){
        for(i=0;i<5;i++){
            printf("%d. %s - %d\n", i+1, menu3[i], price3[i]);
        }
    }
    printf("0. Back\n");
}

void addItem(int shop, int item) {
    if(count >= MAX_ITEMS){
        return;
    }
    if(shop == 1){
        strcpy(selectedItems[count], menu1[item-1]);
        selectedPrices[count] = price1[item-1];
    } else if(shop == 2){
        strcpy(selectedItems[count], menu2[item-1]);
        selectedPrices[count] = price2[item-1];
    } else if(shop == 3){
        strcpy(selectedItems[count], menu3[item-1]);
        selectedPrices[count] = price3[item-1];
    }
    count++;
}

void orderMenu(int shop) {
    int item;
    while(1){
        showMenu(shop);
        printf("Select item: ");
        scanf("%d", &item);
        if(item == 0){
            return;
        }
        if(item >= 1 && item <= 5){
            addItem(shop, item);
            printf("Added.\n");
        } else {
            printf("Invalid.\n");
        }
    }
}

int calculateBill() {
    int total=0,i = 0;
    for( i=0;i<count;i++){
        total += selectedPrices[i];
    }
    return total;
}

int deliveryFee() {
    return 30;
}

int discount(int total) {
    if(total > 500){
        return 50;
    }
    return 0;
}

void saveToFile(char name[], char roll[], char room[]) {
    FILE *f = fopen("/Users/mudassirkunda/CLionProjects/PF Lab/Project/orders.txt", "a");
    if(f == NULL){
        printf("File Not Found\n");
        return ;
    }

    fprintf(f, "Name: %s\n", name);
    fprintf(f, "Roll: %s\n", roll);
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    fprintf(f,"Order Date: %02d-%02d-%04d\n",t->tm_mday, t->tm_mon + 1, t->tm_year + 1900);
    fprintf(f, "Order Time: %02d:%02d:%02d\n",
            t->tm_hour, t->tm_min, t->tm_sec);
    time_t future_time = now + (30 * 60);
    struct tm *future = localtime(&future_time);

    fprintf(f, "Delivery Time: %02d:%02d:%02d\n",
            future->tm_hour, future->tm_min, future->tm_sec);
    fprintf(f, "Order Status: Confirmed\n");
    fprintf(f, "Room: %s\n", room);
    fprintf(f, "Items:\n");
    int i;

    for( i=0;i<count;i++){
        fprintf(f, "%s - %d\n", selectedItems[i], selectedPrices[i]);
    }

    fprintf(f, "Total Bill: %d\n", calculateBill() + deliveryFee() - discount(calculateBill()));

    fprintf(f, "-------------------------\n");

    fclose(f);
}

void showSummary(char name[], char roll[], char room[]) {
    int i,subtotal = calculateBill();
    int fee = deliveryFee();
    int off = discount(subtotal);
    int final = subtotal + fee - off;

    printf("\nOrder Summary:\n");
    printf("Name: %s\n", name);
    printf("Roll No: %s\n", roll);
    printf("Room: %s\n", room);

    printf("\nItems Ordered:\n");
    if(count == 0){
        printf("No items.\n");
    } else {
        for( i=0;i<count;i++){
            printf("%s - %d\n", selectedItems[i], selectedPrices[i]);
        }

        printf("\nSubtotal: %d\n", subtotal);
        printf("Delivery Fee: %d\n", fee);
        printf("Discount: %d\n", off);
        printf("Total Bill: %d\n", final);
    }
}
void cancelorder(char roll[]) {
    FILE *f = fopen("/Users/mudassirkunda/CLionProjects/PF Lab/Project/orders.txt", "r");
    FILE *temp = fopen("/Users/mudassirkunda/CLionProjects/PF Lab/Project/temp.txt", "w");
    if(f == NULL || temp == NULL){
        printf("File error\n");
        return;
    }

    char line[200];
    int found = 0,inOrder=0;
    int deliveryHour, deliveryMin, deliverySec;
    int deliveryTimeFound = 0;

    while(fgets(line, sizeof(line), f) != NULL){
        if(strstr(line, roll) != NULL){
            found = 1;
            inOrder =1;
            fputs(line, temp);
            continue;
        }
        if (inOrder && strstr(line,"Delivery Time:")!=NULL) {
            sscanf(line, "Delivery Time: %d:%d:%d", &deliveryHour, &deliveryMin, &deliverySec);
            deliveryTimeFound = 1;
            fputs(line, temp);
            continue;
        }
        if(inOrder && strstr(line, "Order Status:") != NULL) {
            if(deliveryTimeFound) {
                time_t now = time(NULL);
                struct tm *t = localtime(&now);
                int curSec = t->tm_hour * 3600 + t->tm_min * 60 + t->tm_sec;
                int deliverySecTotal = deliveryHour * 3600 + deliveryMin * 60 + deliverySec;

                if(curSec >= deliverySecTotal) {
                    printf("You cannot cancel. Order has already been delivered.\n");
                    fputs(line, temp);

                    inOrder = 0;
                    found = 2;
                    continue;
                }
            }
            fprintf(temp, "Order Status: Cancelled\n");
            inOrder = 0;
            found = 1;
            continue;
        }
        fputs(line, temp);
    }

    fclose(f);
    fclose(temp);

    remove("/Users/mudassirkunda/CLionProjects/PF Lab/Project/orders.txt");
    rename("/Users/mudassirkunda/CLionProjects/PF Lab/Project/temp.txt",
           "/Users/mudassirkunda/CLionProjects/PF Lab/Project/orders.txt");

    if(found == 0) {
        printf("Roll number not found.\n");
    } else if(found == 1) {
        printf("Order cancelled successfully.\n");
    }
}

int isValidRoll(char roll[]) {
    if(strlen(roll) != 8) return 0;
    if(!isdigit(roll[0]) || !isdigit(roll[1])) return 0;
    if(!isalpha(roll[2])) return 0;
    if(roll[3] != '-') return 0;
    for(int i = 4; i < 8; i++){
        if(!isdigit(roll[i])) return 0;
    }
    return 1;
}
int validRoom(char room[]) {
    if(strlen(room) != 4) return 0;

    if(!(room[0] >= 'A' && room[0] <= 'Z')) return 0;

    if(room[1] != '-') return 0;

    if(!(room[2] >= '0' && room[2] <= '9')) return 0;
    if(!(room[3] >= '0' && room[3] <= '9')) return 0;

    return 1;
}
void orderstatus(char roll[]) {
    FILE *f = fopen("/Users/mudassirkunda/CLionProjects/PF Lab/Project/orders.txt", "r");
    if(f == NULL) {
        printf("File error\n");
    }
    char line[200];

    int dHour, dMin, dSec;
    int found = 0;
    while(fgets(line, sizeof(line), f) != NULL) {
        if(strstr(line, roll) != NULL) {
            found =1 ;
        }
        if (found && strstr(line,"Delivery Time:") != NULL) {
           sscanf(line, "Delivery Time: %d:%d:%d", &dHour, &dMin, &dSec);            break;
        }
    }
    fclose(f);
    if(!found){
        printf("Roll number not found.\n");
        return;
    }
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    int curSec = t->tm_hour*3600 + t->tm_min*60 + t->tm_sec;
    int deliverySec = dHour*3600 + dMin*60 + dSec;
    int diff = deliverySec - curSec;
    if(diff <= 0){
        printf("Your order should have been delivered.\n");
        return;
    }
    int minutes = diff / 60;

    printf("Your order will be delivered in %d minutes.\n", minutes);
}




int main_1() {
    int mainChoice, shopChoice, confirm;
    char name[50], roll[9], room[20];

    while(1){
        printf("\n1. Start Order\n2. Cancel Order\n3. Order Status\n4. Exit");
        scanf("%d", &mainChoice);

        if(mainChoice == 4){

            return 0;
        }

        if(mainChoice == 1){
            count = 0;

            printf("Enter Name: ");
            scanf("%s", name);


            printf("Enter Roll No (e.g. 25k-0098): ");
            scanf("%s", roll);
            while (!isValidRoll(roll)) {
                printf("Roll Number is invalid. Enter again in the format XXk-XXXX\n");
                scanf("%s", roll);
            }



            printf("Enter Room (e.g. E-33): ");
            scanf("%s", room);
            while (!validRoom(room)) {
                printf("Room Number is invalid. Enter again in the format E-31\n");
                scanf("%s", room);

            }


            while(1){
                shopChoice = selectShop();
                if(shopChoice == 4){
                    break;
                }
                if(shopChoice >= 1 && shopChoice <= 3){
                    orderMenu(shopChoice);
                }
            }

            showSummary(name, roll, room);

            if(count > 0){
                printf("\nConfirm Order? (1 = Yes, 0 = No): ");
                scanf("%d", &confirm);

                if(confirm == 1){
                    printf("Order Placed Successfully.\n");
                    saveToFile(name, roll, room);
                } else {
                    printf("Order Cancelled.\n");
                }
            } else {
                printf("\nNo items selected.\n");
            }
        }
        else if(mainChoice == 2) {
            printf("Enter Roll No (e.g. 25k-0098): ");
            scanf("%s", roll);
            while (!isValidRoll(roll)) {
                printf("Roll Number is invalid. Enter again in the format XXk-XXXX\n");
                scanf("%s", roll);
            }
            cancelorder(roll);

        }
        else if(mainChoice == 3) {
            printf("Enter Roll No (e.g. 25k-0098): ");
            scanf("%s", roll);
            while (!isValidRoll(roll)) {
                printf("Roll Number is invalid. Enter again in the format XXk-XXXX\n");
                scanf("%s", roll);
            }
            orderstatus(roll);
        }
    }
}
