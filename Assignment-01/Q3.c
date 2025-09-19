#include <stdio.h>

int main() {
    printf("This program is to check if you are eligible for a driver's license\n");
    printf("Please enter your age:\n");

    int age;
    scanf("%d", &age);

    if (age >= 18) {
        printf("Have you passed the Eye test? (Y/N)\n");
        char eyeTest;
        scanf(" %c", &eyeTest);

        if (eyeTest == 'Y' || eyeTest == 'y') {
            printf("Have you passed your written test? (Y/N)\n");
            char writtenTest;
            scanf(" %c", &writtenTest);

            if (writtenTest == 'Y' || writtenTest == 'y') {
                printf("Have you passed your driving test? (Y/N)\n");
                char drivingTest;
                scanf(" %c", &drivingTest);

                if (drivingTest == 'Y' || drivingTest == 'y') {
                    if (age < 60) {
                        printf("You are eligible for a driver's license\n");
                    } else {
                        printf("You need a medical fitness certificate.\n");
                        printf("Do you have one? (Y/N)\n");
                        char medicalCert;
                        scanf(" %c", &medicalCert);

                        if (medicalCert == 'Y' || medicalCert == 'y') {
                            printf("You are eligible for a driver's license\n");
                        } else {
                            printf("You are not eligible for a driver's license\n");
                        }
                    }
                } else {
                    printf("You are not eligible for a driver's license\n");
                }
            } else {
                printf("You are not eligible for a driver's license\n");
            }
        } else {
            printf("You are not eligible for a driver's license\n");
        }
    } else {
        printf("You are not eligible for a driver's license\n");
    }

    return 0;
}