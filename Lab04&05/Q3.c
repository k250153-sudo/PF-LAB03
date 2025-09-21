#include <stdio.h>
int main() {
    char item,type;
    printf("You want to manage books or magzines. Enter B for books or M for magzines:");
    scanf(" %c",&item);
    printf("You want to issue or return. Enter R for return or I for issue:");
    scanf(" %c",&type);
    switch (item) {
        case 'B':
            switch (type) {
             case 'R':
                    printf("Your book has been returned");
                    break;
             case 'I':
                 printf("You book has been issued");
                 break;

            }
            break;
        case 'M':
            switch (type) {
            case 'R':
                    printf("Your magzine has been returned");
                    break;
            case 'I':
                    printf("You magzine has been issued");
                    break;

            }
            break;
    }
}
