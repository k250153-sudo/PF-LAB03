#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "project.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

// Screen dimensions
#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 700

// GUI States
typedef enum {
    SCREEN_MAIN_MENU = 0,
    SCREEN_ENTER_DETAILS,
    SCREEN_SHOP_SELECTION,
    SCREEN_MENU_VIEW,
    SCREEN_CART_VIEW,
    SCREEN_ORDER_SUMMARY,
    SCREEN_ORDER_CONFIRMATION,
    SCREEN_CANCEL_ORDER,
    SCREEN_ORDER_STATUS
} ScreenState;

// Global variables
ScreenState currentScreen = SCREEN_MAIN_MENU;
Order currentOrder = {0};
int selectedShop = -1;
bool editingName = false;
bool editingRoll = false;
bool editingRoom = false;
char statusMessage[500] = "";
float messageTimer = 0.0f;
Color messageColor;

// Scroll values
Vector2 menuScroll = {0, 0};
Vector2 cartScroll = {0, 0};

// Shop and menu initialization
char shops[3][50] = {"FAST Canteen", "CS Block Snacks", "Main Gate Juice Bar"};
char menu1[5][50] = {"Burger", "Fries", "Zinger", "Roll", "Drink"};
int price1[5] = {200, 100, 250, 120, 80};
char menu2[5][50] = {"Patties", "Sandwich", "Chips", "Cup Cake", "Tea"};
int price2[5] = {40, 120, 50, 70, 30};
char menu3[5][50] = {"Mango Shake", "Strawberry Shake", "Oreo Shake", "Cold Coffee", "Water"};
int price3[5] = {150, 180, 200, 160, 40};

// Helper functions
void ShowMessage(const char* message, Color color) {
    strncpy(statusMessage, message, sizeof(statusMessage) - 1);
    messageColor = color;
    messageTimer = 3.0f;
}

void clearOrder(Order* order) {
    memset(order, 0, sizeof(Order));
}

int isValidRoll(const char* roll) {
    if(strlen(roll) != 8) return 0;
    if(!isdigit(roll[0]) || !isdigit(roll[1])) return 0;
    if(!isalpha(roll[2])) return 0;
    if(roll[3] != '-') return 0;
    for(int i = 4; i < 8; i++){
        if(!isdigit(roll[i])) return 0;
    }
    return 1;
}

int isValidRoom(const char* room) {
    if(strlen(room) != 4) return 0;
    if(!(room[0] >= 'A' && room[0] <= 'Z')) return 0;
    if(room[1] != '-') return 0;
    if(!(room[2] >= '0' && room[2] <= '9')) return 0;
    if(!(room[3] >= '0' && room[3] <= '9')) return 0;
    return 1;
}

int calculateSubtotal(Order* order) {
    int total = 0;
    for(int i = 0; i < order->itemCount; i++) {
        total += order->prices[i];
    }
    return total;
}

int calculateDiscount(int subtotal) {
    return (subtotal > 500) ? 50 : 0;
}

int calculateTotal(Order* order) {
    order->subtotal = calculateSubtotal(order);
    order->deliveryFee = 30;
    order->discount = calculateDiscount(order->subtotal);
    order->total = order->subtotal + order->deliveryFee - order->discount;
    return order->total;
}

void addItemToOrder(Order* order, int shop, int itemIndex) {
    if(order->itemCount >= MAX_ITEMS) return;

    if(shop == 0) {
        strcpy(order->items[order->itemCount], menu1[itemIndex]);
        order->prices[order->itemCount] = price1[itemIndex];
    } else if(shop == 1) {
        strcpy(order->items[order->itemCount], menu2[itemIndex]);
        order->prices[order->itemCount] = price2[itemIndex];
    } else if(shop == 2) {
        strcpy(order->items[order->itemCount], menu3[itemIndex]);
        order->prices[order->itemCount] = price3[itemIndex];
    }
    order->itemCount++;
}

void removeItemFromOrder(Order* order, int index) {
    if(index < 0 || index >= order->itemCount) return;

    for(int i = index; i < order->itemCount - 1; i++) {
        strcpy(order->items[i], order->items[i + 1]);
        order->prices[i] = order->prices[i + 1];
    }
    order->itemCount--;
}

void saveOrderToFile(Order* order) {
    FILE *f = fopen("orders.txt", "a");
    if(f == NULL) return;

    fprintf(f, "Name: %s\n", order->name);
    fprintf(f, "Roll: %s\n", order->roll);

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    fprintf(f, "Order Date: %02d-%02d-%04d\n", t->tm_mday, t->tm_mon + 1, t->tm_year + 1900);
    fprintf(f, "Order Time: %02d:%02d:%02d\n", t->tm_hour, t->tm_min, t->tm_sec);

    time_t future_time = now + (30 * 60);
    struct tm *future = localtime(&future_time);
    fprintf(f, "Delivery Time: %02d:%02d:%02d\n", future->tm_hour, future->tm_min, future->tm_sec);
    fprintf(f, "Order Status: Confirmed\n");
    fprintf(f, "Room: %s\n", order->room);
    fprintf(f, "Items:\n");

    for(int i = 0; i < order->itemCount; i++) {
        fprintf(f, "%s - %d\n", order->items[i], order->prices[i]);
    }

    fprintf(f, "Total Bill: %d\n", order->total);
    fprintf(f, "-------------------------\n");

    fclose(f);
}

void cancelOrderByRoll(const char* roll, char* resultMessage) {
    FILE *f = fopen("orders.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if(f == NULL || temp == NULL) {
        strcpy(resultMessage, "Error: Cannot access order file");
        if(f) fclose(f);
        if(temp) fclose(temp);
        return;
    }

    char line[200];
    int found = 0, inOrder = 0;
    int deliveryHour, deliveryMin, deliverySec;
    int deliveryTimeFound = 0;

    while(fgets(line, sizeof(line), f) != NULL) {
        if(strstr(line, roll) != NULL) {
            found = 1;
            inOrder = 1;
            fputs(line, temp);
            continue;
        }

        if(inOrder && strstr(line, "Delivery Time:") != NULL) {
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
                    strcpy(resultMessage, "Cannot cancel: Order already delivered");
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

    remove("orders.txt");
    rename("temp.txt", "orders.txt");

    if(found == 0) {
        strcpy(resultMessage, "Roll number not found");
    } else if(found == 1) {
        strcpy(resultMessage, "Order cancelled successfully!");
    }
}

void getOrderStatus(const char* roll, char* resultMessage) {
    FILE *f = fopen("orders.txt", "r");
    if(f == NULL) {
        strcpy(resultMessage, "Error: Cannot access order file");
        return;
    }

    char line[200];
    int dHour, dMin, dSec;
    int found = 0;

    while(fgets(line, sizeof(line), f) != NULL) {
        if(strstr(line, roll) != NULL) {
            found = 1;
        }
        if(found && strstr(line, "Delivery Time:") != NULL) {
            sscanf(line, "Delivery Time: %d:%d:%d", &dHour, &dMin, &dSec);
            break;
        }
    }
    fclose(f);

    if(!found) {
        strcpy(resultMessage, "Roll number not found");
        return;
    }

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    int curSec = t->tm_hour * 3600 + t->tm_min * 60 + t->tm_sec;
    int deliverySec = dHour * 3600 + dMin * 60 + dSec;
    int diff = deliverySec - curSec;

    if(diff <= 0) {
        sprintf(resultMessage, "Your order has been delivered!\nDelivery time was: %02d:%02d:%02d", dHour, dMin, dSec);
    } else {
        int minutes = diff / 60;
        sprintf(resultMessage, "Your order will be delivered in %d minutes\nEstimated time: %02d:%02d:%02d", minutes, dHour, dMin, dSec);
    }
}

// Draw functions for each screen
void DrawMainMenu() {
    DrawText("FAST NUCES", SCREEN_WIDTH/2 - 180, 80, 60, DARKBLUE);
    DrawText("Food Delivery System", SCREEN_WIDTH/2 - 180, 150, 30, DARKGRAY);

    Rectangle btnRect = {SCREEN_WIDTH/2 - 150, 250, 300, 60};

    if(GuiButton(btnRect, "#132# Start New Order")) {
        clearOrder(&currentOrder);
        currentScreen = SCREEN_ENTER_DETAILS;
    }

    btnRect.y += 80;
    if(GuiButton(btnRect, "#143# Cancel Order")) {
        currentScreen = SCREEN_CANCEL_ORDER;
        memset(currentOrder.roll, 0, sizeof(currentOrder.roll));
    }

    btnRect.y += 80;
    if(GuiButton(btnRect, "#120# Order Status")) {
        currentScreen = SCREEN_ORDER_STATUS;
        memset(currentOrder.roll, 0, sizeof(currentOrder.roll));
    }

    btnRect.y += 80;
    if(GuiButton(btnRect, "#159# Exit")) {
        CloseWindow();
    }
}

void DrawEnterDetails() {
    DrawText("Enter Your Details", SCREEN_WIDTH/2 - 170, 80, 40, DARKBLUE);

    Rectangle nameBox = {SCREEN_WIDTH/2 - 200, 180, 400, 40};
    Rectangle rollBox = {SCREEN_WIDTH/2 - 200, 250, 400, 40};
    Rectangle roomBox = {SCREEN_WIDTH/2 - 200, 320, 400, 40};

    DrawText("Name:", nameBox.x, nameBox.y - 25, 20, DARKGRAY);
    if(GuiTextBox(nameBox, currentOrder.name, MAX_NAME_LENGTH, editingName)) {
        editingName = !editingName;
    }

    DrawText("Roll No (e.g. 25k-0098):", rollBox.x, rollBox.y - 25, 20, DARKGRAY);
    if(GuiTextBox(rollBox, currentOrder.roll, MAX_ROLL_LENGTH, editingRoll)) {
        editingRoll = !editingRoll;
    }

    DrawText("Room (e.g. E-33):", roomBox.x, roomBox.y - 25, 20, DARKGRAY);
    if(GuiTextBox(roomBox, currentOrder.room, MAX_ROOM_LENGTH, editingRoom)) {
        editingRoom = !editingRoom;
    }

    Rectangle btnContinue = {SCREEN_WIDTH/2 - 100, 420, 200, 50};
    Rectangle btnBack = {SCREEN_WIDTH/2 - 100, 490, 200, 50};

    if(GuiButton(btnContinue, "#114# Continue")) {
        if(strlen(currentOrder.name) == 0) {
            ShowMessage("Please enter your name", RED);
        } else if(!isValidRoll(currentOrder.roll)) {
            ShowMessage("Invalid roll number format", RED);
        } else if(!isValidRoom(currentOrder.room)) {
            ShowMessage("Invalid room format", RED);
        } else {
            currentScreen = SCREEN_SHOP_SELECTION;
        }
    }

    if(GuiButton(btnBack, "#113# Back")) {
        currentScreen = SCREEN_MAIN_MENU;
    }
}

void DrawShopSelection() {
    DrawText("Select Shop", SCREEN_WIDTH/2 - 130, 80, 40, DARKBLUE);

    char info[100];
    sprintf(info, "Welcome, %s!", currentOrder.name);
    DrawText(info, SCREEN_WIDTH/2 - MeasureText(info, 20)/2, 140, 20, DARKGRAY);

    Rectangle shopBtn = {SCREEN_WIDTH/2 - 200, 200, 400, 70};

    for(int i = 0; i < 3; i++) {
        if(GuiButton(shopBtn, shops[i])) {
            selectedShop = i;
            currentScreen = SCREEN_MENU_VIEW;
        }
        shopBtn.y += 90;
    }

    Rectangle btnCart = {SCREEN_WIDTH/2 - 200, 520, 180, 50};
    Rectangle btnBack = {SCREEN_WIDTH/2 + 20, 520, 180, 50};

    char cartText[50];
    sprintf(cartText, "#193# Cart (%d)", currentOrder.itemCount);
    if(GuiButton(btnCart, cartText)) {
        currentScreen = SCREEN_CART_VIEW;
    }

    if(GuiButton(btnBack, "#113# Back")) {
        currentScreen = SCREEN_ENTER_DETAILS;
    }
}

void DrawMenuView() {
    DrawText(shops[selectedShop], SCREEN_WIDTH/2 - MeasureText(shops[selectedShop], 40)/2, 30, 40, DARKBLUE);

    Rectangle menuArea = {50, 90, SCREEN_WIDTH - 100, SCREEN_HEIGHT - 200};

    char (*menu)[50];
    int *prices;

    if(selectedShop == 0) {
        menu = menu1;
        prices = price1;
    } else if(selectedShop == 1) {
        menu = menu2;
        prices = price2;
    } else {
        menu = menu3;
        prices = price3;
    }

    Rectangle itemCard = {70, 110, SCREEN_WIDTH - 140, 80};

    for(int i = 0; i < 5; i++) {
        DrawRectangleRec(itemCard, Fade(LIGHTGRAY, 0.3f));
        DrawRectangleLinesEx(itemCard, 2, DARKGRAY);

        char itemText[100];
        sprintf(itemText, "%s", menu[i]);
        DrawText(itemText, itemCard.x + 20, itemCard.y + 15, 25, DARKBLUE);

        sprintf(itemText, "Rs. %d", prices[i]);
        DrawText(itemText, itemCard.x + 20, itemCard.y + 45, 20, DARKGREEN);

        Rectangle addBtn = {itemCard.x + itemCard.width - 120, itemCard.y + 20, 100, 40};
        if(GuiButton(addBtn, "#132# Add")) {
            addItemToOrder(&currentOrder, selectedShop, i);
            ShowMessage("Item added to cart!", GREEN);
        }

        itemCard.y += 95;
    }

    Rectangle btnBack = {50, SCREEN_HEIGHT - 80, 150, 50};
    Rectangle btnCart = {SCREEN_WIDTH - 200, SCREEN_HEIGHT - 80, 150, 50};

    if(GuiButton(btnBack, "#113# Back")) {
        currentScreen = SCREEN_SHOP_SELECTION;
    }

    char cartText[50];
    sprintf(cartText, "#193# Cart (%d)", currentOrder.itemCount);
    if(GuiButton(btnCart, cartText)) {
        currentScreen = SCREEN_CART_VIEW;
    }
}

void DrawCartView() {
    DrawText("Shopping Cart", SCREEN_WIDTH/2 - 150, 30, 40, DARKBLUE);

    if(currentOrder.itemCount == 0) {
        DrawText("Your cart is empty", SCREEN_WIDTH/2 - 120, SCREEN_HEIGHT/2 - 30, 25, DARKGRAY);
    } else {
        Rectangle itemCard = {70, 90, SCREEN_WIDTH - 140, 60};

        for(int i = 0; i < currentOrder.itemCount; i++) {
            DrawRectangleRec(itemCard, Fade(LIGHTGRAY, 0.3f));
            DrawRectangleLinesEx(itemCard, 2, DARKGRAY);

            DrawText(currentOrder.items[i], itemCard.x + 20, itemCard.y + 10, 22, DARKBLUE);

            char priceText[30];
            sprintf(priceText, "Rs. %d", currentOrder.prices[i]);
            DrawText(priceText, itemCard.x + 20, itemCard.y + 35, 18, DARKGREEN);

            Rectangle removeBtn = {itemCard.x + itemCard.width - 120, itemCard.y + 10, 100, 40};
            if(GuiButton(removeBtn, "#143# Remove")) {
                removeItemFromOrder(&currentOrder, i);
                ShowMessage("Item removed", ORANGE);
                break;
            }

            itemCard.y += 70;
        }

        // Display totals
        calculateTotal(&currentOrder);
        int yPos = SCREEN_HEIGHT - 220;
        DrawRectangle(SCREEN_WIDTH - 350, yPos - 10, 330, 140, Fade(SKYBLUE, 0.3f));
        DrawRectangleLinesEx((Rectangle){SCREEN_WIDTH - 350, yPos - 10, 330, 140}, 2, DARKBLUE);

        char text[50];
        sprintf(text, "Subtotal: Rs. %d", currentOrder.subtotal);
        DrawText(text, SCREEN_WIDTH - 330, yPos, 20, DARKGRAY);

        sprintf(text, "Delivery Fee: Rs. %d", currentOrder.deliveryFee);
        DrawText(text, SCREEN_WIDTH - 330, yPos + 30, 20, DARKGRAY);

        sprintf(text, "Discount: Rs. %d", currentOrder.discount);
        DrawText(text, SCREEN_WIDTH - 330, yPos + 60, 20, RED);

        sprintf(text, "Total: Rs. %d", currentOrder.total);
        DrawText(text, SCREEN_WIDTH - 330, yPos + 95, 24, DARKGREEN);
    }

    Rectangle btnBack = {50, SCREEN_HEIGHT - 80, 150, 50};
    Rectangle btnCheckout = {SCREEN_WIDTH - 250, SCREEN_HEIGHT - 80, 200, 50};

    if(GuiButton(btnBack, "#113# Back")) {
        currentScreen = SCREEN_SHOP_SELECTION;
    }

    if(currentOrder.itemCount > 0) {
        if(GuiButton(btnCheckout, "#120# Checkout")) {
            currentScreen = SCREEN_ORDER_SUMMARY;
        }
    }
}

void DrawOrderSummary() {
    DrawText("Order Summary", SCREEN_WIDTH/2 - 150, 30, 40, DARKBLUE);

    int yPos = 90;
    DrawText("Customer Details:", 50, yPos, 25, DARKGRAY);
    yPos += 35;

    char text[100];
    sprintf(text, "Name: %s", currentOrder.name);
    DrawText(text, 70, yPos, 20, BLACK);
    yPos += 30;

    sprintf(text, "Roll No: %s", currentOrder.roll);
    DrawText(text, 70, yPos, 20, BLACK);
    yPos += 30;

    sprintf(text, "Room: %s", currentOrder.room);
    DrawText(text, 70, yPos, 20, BLACK);
    yPos += 40;

    DrawText("Items Ordered:", 50, yPos, 25, DARKGRAY);
    yPos += 35;

    for(int i = 0; i < currentOrder.itemCount && yPos < SCREEN_HEIGHT - 220; i++) {
        sprintf(text, "%d. %s - Rs. %d", i+1, currentOrder.items[i], currentOrder.prices[i]);
        DrawText(text, 70, yPos, 20, DARKBLUE);
        yPos += 28;
    }

    yPos = SCREEN_HEIGHT - 190;
    DrawRectangle(SCREEN_WIDTH - 350, yPos - 10, 330, 140, Fade(LIGHTGRAY, 0.5f));
    DrawRectangleLinesEx((Rectangle){SCREEN_WIDTH - 350, yPos - 10, 330, 140}, 2, DARKBLUE);

    sprintf(text, "Subtotal: Rs. %d", currentOrder.subtotal);
    DrawText(text, SCREEN_WIDTH - 330, yPos, 20, DARKGRAY);

    sprintf(text, "Delivery Fee: Rs. %d", currentOrder.deliveryFee);
    DrawText(text, SCREEN_WIDTH - 330, yPos + 30, 20, DARKGRAY);

    sprintf(text, "Discount: Rs. %d", currentOrder.discount);
    DrawText(text, SCREEN_WIDTH - 330, yPos + 60, 20, RED);

    sprintf(text, "Total: Rs. %d", currentOrder.total);
    DrawText(text, SCREEN_WIDTH - 330, yPos + 95, 24, DARKGREEN);

    Rectangle btnConfirm = {SCREEN_WIDTH/2 - 200, SCREEN_HEIGHT - 80, 180, 50};
    Rectangle btnCancel = {SCREEN_WIDTH/2 + 20, SCREEN_HEIGHT - 80, 180, 50};

    if(GuiButton(btnConfirm, "#120# Confirm Order")) {
        saveOrderToFile(&currentOrder);
        currentScreen = SCREEN_ORDER_CONFIRMATION;
    }

    if(GuiButton(btnCancel, "#113# Back")) {
        currentScreen = SCREEN_CART_VIEW;
    }
}

void DrawOrderConfirmation() {
    DrawText("Order Confirmed!", SCREEN_WIDTH/2 - 180, 150, 45, DARKGREEN);

    DrawText("Your order has been placed successfully!", SCREEN_WIDTH/2 - 230, 230, 22, DARKGRAY);
    DrawText("Estimated delivery time: 30 minutes", SCREEN_WIDTH/2 - 200, 270, 22, DARKGRAY);

    char text[100];
    sprintf(text, "Order for: %s (%s)", currentOrder.name, currentOrder.roll);
    DrawText(text, SCREEN_WIDTH/2 - MeasureText(text, 20)/2, 320, 20, BLACK);

    sprintf(text, "Delivery to: Room %s", currentOrder.room);
    DrawText(text, SCREEN_WIDTH/2 - MeasureText(text, 20)/2, 350, 20, BLACK);

    sprintf(text, "Total Amount: Rs. %d", currentOrder.total);
    DrawText(text, SCREEN_WIDTH/2 - MeasureText(text, 24)/2, 390, 24, DARKGREEN);

    Rectangle btnHome = {SCREEN_WIDTH/2 - 100, 470, 200, 50};
    if(GuiButton(btnHome, "#132# Return to Home")) {
        clearOrder(&currentOrder);
        currentScreen = SCREEN_MAIN_MENU;
    }
}

void DrawCancelOrder() {
    DrawText("Cancel Order", SCREEN_WIDTH/2 - 140, 80, 40, DARKBLUE);

    Rectangle rollBox = {SCREEN_WIDTH/2 - 200, 200, 400, 40};

    DrawText("Enter Roll No to cancel:", rollBox.x, rollBox.y - 25, 20, DARKGRAY);
    if(GuiTextBox(rollBox, currentOrder.roll, MAX_ROLL_LENGTH, editingRoll)) {
        editingRoll = !editingRoll;
    }

    Rectangle btnCancel = {SCREEN_WIDTH/2 - 100, 300, 200, 50};
    Rectangle btnBack = {SCREEN_WIDTH/2 - 100, 370, 200, 50};

    if(GuiButton(btnCancel, "#143# Cancel Order")) {
        if(!isValidRoll(currentOrder.roll)) {
            ShowMessage("Invalid roll number format", RED);
        } else {
            char result[500];
            cancelOrderByRoll(currentOrder.roll, result);
            if(strstr(result, "successfully") != NULL) {
                ShowMessage(result, GREEN);
            } else {
                ShowMessage(result, RED);
            }
        }
    }

    if(GuiButton(btnBack, "#113# Back")) {
        currentScreen = SCREEN_MAIN_MENU;
    }
}

void DrawOrderStatus() {
    DrawText("Order Status", SCREEN_WIDTH/2 - 130, 80, 40, DARKBLUE);

    Rectangle rollBox = {SCREEN_WIDTH/2 - 200, 200, 400, 40};

    DrawText("Enter Roll No:", rollBox.x, rollBox.y - 25, 20, DARKGRAY);
    if(GuiTextBox(rollBox, currentOrder.roll, MAX_ROLL_LENGTH, editingRoll)) {
        editingRoll = !editingRoll;
    }

    Rectangle btnCheck = {SCREEN_WIDTH/2 - 100, 300, 200, 50};
    Rectangle btnBack = {SCREEN_WIDTH/2 - 100, 370, 200, 50};

    if(GuiButton(btnCheck, "#120# Check Status")) {
        if(!isValidRoll(currentOrder.roll)) {
            ShowMessage("Invalid roll number format", RED);
        } else {
            char result[500];
            getOrderStatus(currentOrder.roll, result);
            ShowMessage(result, DARKBLUE);
        }
    }

    if(GuiButton(btnBack, "#113# Back")) {
        currentScreen = SCREEN_MAIN_MENU;
    }
}

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "FAST NUCES Food Delivery");
    SetTargetFPS(60);

    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
    GuiSetStyle(BUTTON, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);

    while(!WindowShouldClose()) {
        // Update
        if(messageTimer > 0) {
            messageTimer -= GetFrameTime();
        }

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        switch(currentScreen) {
            case SCREEN_MAIN_MENU:
                DrawMainMenu();
                break;
            case SCREEN_ENTER_DETAILS:
                DrawEnterDetails();
                break;
            case SCREEN_SHOP_SELECTION:
                DrawShopSelection();
                break;
            case SCREEN_MENU_VIEW:
                DrawMenuView();
                break;
            case SCREEN_CART_VIEW:
                DrawCartView();
                break;
            case SCREEN_ORDER_SUMMARY:
                DrawOrderSummary();
                break;
            case SCREEN_ORDER_CONFIRMATION:
                DrawOrderConfirmation();
                break;
            case SCREEN_CANCEL_ORDER:
                DrawCancelOrder();
                break;
            case SCREEN_ORDER_STATUS:
                DrawOrderStatus();
                break;
        }

        // Draw status message
        if(messageTimer > 0) {
            Rectangle msgBox = {SCREEN_WIDTH/2 - 250, 20, 500, 50};
            DrawRectangleRec(msgBox, Fade(messageColor, 0.8f));
            DrawRectangleLinesEx(msgBox, 2, BLACK);
            DrawText(statusMessage, msgBox.x + 10, msgBox.y + 15, 20, WHITE);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}