#include <stdio.h>
#include <string.h>

char* formatFullName(char* first, char* last) {
    static char fullname[100];
    strcpy(fullname, first);
    strcat(fullname, " ");
    strcat(fullname, last);
    return fullname;
}

int main() {
    char firstName[50], lastName[50];

    printf("Enter first name: ");
    scanf("%49s", firstName);

    printf("Enter last name: ");
    scanf("%49s", lastName);

    char* fullName = formatFullName(firstName, lastName);

    printf("Full name: %s\n", fullName);

    return 0;
}