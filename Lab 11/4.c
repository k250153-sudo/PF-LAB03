#include <stdio.h>
#include <string.h>

void reverseRec(char word[], int start, int end) {
    if (start >= end) return;

    char temp = word[start];
    word[start] = word[end];
    word[end] = temp;

    reverseRec(word, start + 1, end - 1);
}

int isPalindromeRec(char word[], int start, int end) {
    if (start >= end) return 1;
    if (word[start] != word[end]) return 0;

    return isPalindromeRec(word, start + 1, end - 1);
}

int main() {
    char word[100];

    while (1) {
        printf("Enter a word (or 'exit' to quit): ");

        fgets(word, sizeof(word), stdin);
        word[strcspn(word, "\n")] = '\0';
        if (strcmp(word, "exit") == 0)
            break;

        char cleaned[512];
        int j = 0;
        for (int i = 0; word[i] != '\0'; ++i) {
            if (word[i] != ' ') {
                cleaned[j++] = word[i];
            }
        }
        cleaned[j] = '\0';

        char reversed[100];
        strcpy(reversed, cleaned);
        reverseRec(reversed, 0, strlen(reversed) - 1);
        printf("Reversed = %s\n", reversed);
        if (isPalindromeRec(cleaned, 0, strlen(cleaned) - 1))
            printf("Palindrome = Yes\n");
        else
            printf("Palindrome = No\n");
    }

    return 0;
}