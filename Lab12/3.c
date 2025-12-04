#include <stdio.h>
#include <stdlib.h>
#include <c++/v1/cctype>

char *readusername() {
    char *username=(char*)malloc(sizeof(char)*1);
    if (username==NULL) {
        printf("Not enough memory!\n");
        exit(1);
    }
    int index=0,size=1;
    char c;
    while ((c = getchar()) != '\n') {
        username[index]=c;
        size++;
        index++;
        char *temp = realloc(username, size);
        if (temp == NULL) {
            printf("Not enough space\n");
            free(username);
            exit(1);
        }
        username = temp;
    }
    username[index] = '\0';
    return username;
}
int containDigits(char *str) {
    while (*str != '\0') {
        if (isdigit(*str)) {
            return 1;
        }
        str++;
    }
    return 0;
}
int main() {
    int n;
    printf("Enter the number of usernames: ");
    scanf("%d",&n);
    getchar();
    char **username=(char**)malloc(n*sizeof(char*));
    for (int i=0;i<n;i++) {
        printf("Enter the username number &d",i+1);
        username[i]=readusername();
    }
    int check;
    printf("Correct usernames entered:\n");
    for (int i=0;i<n;i++) {
        check=containDigits(username[i]);
        if (check==0) {
            printf("User name is %s\n",username[i]);
        }
    }
    for (int i = 0; i < n; i++) {
        free(username[i]);
    }
    free(username);

}