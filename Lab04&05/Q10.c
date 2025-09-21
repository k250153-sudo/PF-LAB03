#include <stdio.h>
#include <string.h>

int main() {
    int age;
    printf("Enter your age:");
    scanf("%d",&age);
    char t_type[20];
    if (age<12) {
        strcpy(t_type,"Child Ticket");
    }
    else if (age>=12 && age<=60) {
        strcpy(t_type,"Adult Ticket");
    }
    else if (age>60) {
        strcpy(t_type,"Senior Citizen Ticket");
    }
    char m_type[20];
    printf("Movie types are:\n .Action\n .Comedy\n .Horror\nWhat type would you like to watch: ");
    scanf("%s",m_type);
    switch (m_type[0]) {
        case 'A':
            case 'a':
            printf("%s booked for %s",t_type,m_type);
            break;
        case 'C':
        case 'c':
            printf("%s booked for %s",t_type,m_type);
            break;
        case 'H':
        case 'h':
            printf("%s booked for %s",t_type,m_type);
            break;
    }
}