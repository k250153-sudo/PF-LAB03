#include <stdio.h>
#include <string.h>
int main() {
    char username[50];
    printf("Enter your username:");
    scanf("%s",&username);
    if (strcasecmp(username,"admin")==0) {
        char password[50];
        printf("Enter your password:");
        scanf("%s",&password);
        if (strcasecmp(password,"1234")==0) {
            printf("Login successful");
        }
        else {
            printf("Wrong password");
        }

    }
    else {
        printf("Username error");
    }
}