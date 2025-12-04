#include <stdio.h>
#include <stdlib.h>
char *readfeedback() {
    char *str=(char *)malloc(sizeof(char)*1);
    if (str==NULL) {
        printf("Memory Error");
        exit(1);
    }
    int size=1;
    int index=0;
    char c;
    while ((c=getchar()) != '\n') {
        str[index++]=c;
        index++;
        size++;
        char *temp = realloc(str, size);
        if (temp == NULL) {
            printf("Not enough space\n");
            free(str);
            exit(1);
        }
        str = temp;

    }
    str[index]='\0';
    return str;
}

int main() {
    printf("Enter the number of feedback entries: ");
    int n;
    scanf("%d",&n);
    getchar();
    char **feedbacks=(char**)malloc(n*sizeof(char*));
    for (int i=0;i<n;i++) {
        printf("Enter feedback entry %d: ",i+1);
        feedbacks[i]=readfeedback();
    }
    int maxLength = 0;
    char *longest = NULL;

    for (int i = 0; i < n; i++) {
        char *ptr = feedbacks[i];
        int len = 0;
        while (*ptr != '\0') {
            len++;
            ptr++;
        }
        if (len > maxLength) {
            maxLength = len;
            longest = feedbacks[i];
        }
    }

    printf("Longest feedback (length %d): %s\n", maxLength, longest);
    int totalChars = 0;
    for (int i = 0; i < n; i++) {
        char *ptr = feedbacks[i];
        while (*ptr != '\0') {
            totalChars++;
            ptr++;
        }
    }
    printf("Total number of characters across all feedbacks: %d\n", totalChars);
    for (int i = 0; i < n; i++) {
        free(feedbacks[i]);
    }
    free(feedbacks);


}