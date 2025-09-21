#include <stdio.h>
int main() {
    char depart[20];
    char course[20];

    printf("The departments are:\n .CS\n .EE\n .BBA\nEnter your department name:");
    scanf("%s",depart);
    switch (depart[0]) {
        case 'C':
            case 'c':
            printf("The courses are:\n .AI\n .DS\n .CY\n .ML\nPlease select your course:");
            scanf("%s",course);
            printf("Your course is %s",course);
            break;
        case 'E':
            case 'e':
            printf("The courses are:\n .CE\n .SS\n .EM\n .PE\nPlease select your course:");
            scanf("%s",course);
            printf("Your course is %s",course);
            break;
        case 'B':
            case 'b':
            printf("The courses are:\n .FM\n .AC\n .MK\n .HR\nPlease select your course:");
            scanf("%s",course);
            printf("Your course is %s",course);
            break;
    }
}