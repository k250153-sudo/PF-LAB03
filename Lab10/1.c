#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void remove_newline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

int main() {
    FILE *fp = fopen("playlist.txt", "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    char arr[10][101];
    int i = 0;
    while (i < 10 && fgets(arr[i], 101, fp) != NULL) {
        remove_newline(arr[i]);
        i++;
    }
    fclose(fp);
    int input;

    do {
        printf("What do you want to do?\n 1-->Add\n 2-->Delete\n 3-->Update\n 4-->Search\n -1-->Exit: ");
        scanf("%d", &input);
        while (getchar() != '\n'); // clear input buffer
        switch (input) {
            case 1:
                if (i >= 10) {
                    printf("Not enough space\n");
                }
                else {
                    printf("Enter your song: ");
                    char song[101];
                    fgets(song, 101, stdin);
                    remove_newline(song);
                    strcpy(arr[i], song);
                    i++;
                }
                break;
            case 2:
                if (i == 0) {
                    printf("File is empty can not delete\n");
                }
                else {
                    printf("Enter the song you want to delete: ");
                    char song[101];
                    fgets(song, 101, stdin);
                    remove_newline(song);
                    bool found = false;
                    for (int j = 0; j < i; j++) {
                        if (strcmp(arr[j], song) == 0) {
                            for (int k = j; k < i - 1; k++) {
                                strcpy(arr[k], arr[k + 1]);
                            }
                            i--;
                            printf("Song deleted successfully.\n");
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        printf("Song not found.\n");
                    }
                }
                break;
            case 3:
                if (i == 0) {
                    printf("File is empty can not update\n");
                }
                else {
                    printf("Enter the song you want to update: ");
                    char song[101];
                    fgets(song, 101, stdin);
                    remove_newline(song);
                    bool found = false;
                    for (int j = 0; j < i; j++) {
                        if (strcmp(arr[j], song) == 0) {
                            found = true;
                            printf("Enter the updated song: ");
                            char u_song[101];
                            fgets(u_song, 101, stdin);
                            remove_newline(u_song);
                            strcpy(arr[j], u_song);
                            break;
                        }
                    }
                    if (!found) {
                        printf("Song not found. Can not update.\n");
                    }
                }
                break;
            case 4:
                if (i == 0) {
                    printf("File is empty can not search\n");
                }
                else {
                    printf("Enter the song you want to search: ");
                    char song[101];
                    fgets(song, 101, stdin);
                    remove_newline(song);
                    bool found = false;
                    for (int j = 0; j < i; j++) {
                        if (strcmp(arr[j], song) == 0) {
                            printf("Song found successfully.\n");
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        printf("Song not found.\n");
                    }
                }
                break;
            case -1:
                for (int x = 0; x < i - 1; x++) {
                    for (int y = 0; y < i - x - 1; y++) {
                        if (strcmp(arr[y], arr[y + 1]) > 0) {
                            char temp[101];
                            strcpy(temp, arr[y]);
                            strcpy(arr[y], arr[y + 1]);
                            strcpy(arr[y + 1], temp);
                        }
                    }
                }
                for (int j = 0; j < i; j++) {
                    printf("%d %s\n", j + 1, arr[j]);
                }
                printf("Exiting....\n");
                break;
            default:
                printf("Invalid option\n");
        }

    } while (input != -1);
    FILE *f = fopen("playlist.txt", "w");
    for (int j = 0; j < i; j++) {
        fprintf(f, "%s\n", arr[j]);
    }
    fclose(f);

}