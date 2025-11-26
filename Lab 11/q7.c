#include <stdio.h>
#include <string.h>

#define MAX_USERS 100
#define MAX_FORECAST_LEN 256

struct Date{
    int day;
    int month;
};

struct Zodiac{
    char name[20];
    char forecast[MAX_FORECAST_LEN];
};

struct User {
    char name[50];
    struct Date birthdate;
    struct Zodiac zodiac;
};

struct Zodiac zodiacSigns[] = {
    {"Capricorn", "Today is a good day to focus on your goals."},
    {"Aquarius", "Expect new opportunities in your social life."},
    {"Pisces", "Creativity will lead you to success."},
    {"Aries", "Take initiative and be confident."},
    {"Taurus", "Patience will bring rewards."},
    {"Gemini", "Communication is key today."},
    {"Cancer", "Trust your intuition."},
    {"Leo", "Your leadership will be recognized."},
    {"Virgo", "Attention to detail will pay off."},
    {"Libra", "Seek balance in your relationships."},
    {"Scorpio", "Embrace change and transformation."},
    {"Sagittarius", "Adventure awaits you."}
};

int getZodiacIndex(struct Date birthdate) {
    int day = birthdate.day;
    int month = birthdate.month;
    // Zodiac date ranges
    if ((month == 12 && day >= 22) || (month == 1 && day <= 19))
        return 0; // Capricorn
    else if ((month == 1 && day >= 20) || (month == 2 && day <= 18))
        return 1; // Aquarius
    else if ((month == 2 && day >= 19) || (month == 3 && day <= 20))
        return 2; // Pisces
    else if ((month == 3 && day >= 21) || (month == 4 && day <= 19))
        return 3; // Aries
    else if ((month == 4 && day >= 20) || (month == 5 && day <= 20))
        return 4; // Taurus
    else if ((month == 5 && day >= 21) || (month == 6 && day <= 20))
        return 5; // Gemini
    else if ((month == 6 && day >= 21) || (month == 7 && day <= 22))
        return 6; // Cancer
    else if ((month == 7 && day >= 23) || (month == 8 && day <= 22))
        return 7; // Leo
    else if ((month == 8 && day >= 23) || (month == 9 && day <= 22))
        return 8; // Virgo
    else if ((month == 9 && day >= 23) || (month == 10 && day <= 22))
        return 9; // Libra
    else if ((month == 10 && day >= 23) || (month == 11 && day <= 21))
        return 10; // Scorpio
    else if ((month == 11 && day >= 22) || (month == 12 && day <= 21))
        return 11; // Sagittarius
    return -1; // Invalid date
}

void inputUser(struct User *user) {
    printf("Enter user name: ");
    fgets(user->name, sizeof(user->name), stdin);
    user->name[strcspn(user->name, "\n")] = 0;

    printf("Enter birth date (day month): ");
    scanf("%d %d", &user->birthdate.day, &user->birthdate.month);
    while(getchar() != '\n');

    int zodiacIndex = getZodiacIndex(user->birthdate);
    if (zodiacIndex == -1) {
        printf("Invalid birth date entered. Setting zodiac to Capricorn by default.\n");
        zodiacIndex = 0;
    }
    strcpy(user->zodiac.name, zodiacSigns[zodiacIndex].name);
    strcpy(user->zodiac.forecast, zodiacSigns[zodiacIndex].forecast);
}

void displayUserHoroscope(struct User *user) {
    printf("\nUser: %s\n", user->name);
    printf("Zodiac Sign: %s\n", user->zodiac.name);
    printf("Today's Forecast: %s\n", user->zodiac.forecast);
}

void updateForecast(struct Zodiac *zodiac) {
    printf("Updating forecast for %s.\n", zodiac->name);
    printf("Enter new forecast: ");
    fgets(zodiac->forecast, MAX_FORECAST_LEN, stdin);
    zodiac->forecast[strcspn(zodiac->forecast, "\n")] = 0; // Remove newline
    printf("Forecast updated.\n");
}

int main() {
    struct User users[MAX_USERS];
    int userCount = 0;
    int choice;

    do {
        printf("\n--- Zodiac Horoscope Manager ---\n");
        printf("1. Add User\n");
        printf("2. Display User Horoscope\n");
        printf("3. Update Zodiac Forecast\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        while(getchar() != '\n');

        switch(choice) {
            case 1:
                if (userCount >= MAX_USERS) {
                    printf("User limit reached.\n");
                } else {
                    inputUser(&users[userCount]);
                    userCount++;
                }
                break;
            case 2:
                if (userCount == 0) {
                    printf("No users available.\n");
                } else {
                    printf("Enter user number (1 to %d): ", userCount);
                    int userNum;
                    scanf("%d", &userNum);
                    while(getchar() != '\n');
                    if (userNum < 1 || userNum > userCount) {
                        printf("Invalid user number.\n");
                    } else {
                        displayUserHoroscope(&users[userNum -1]);
                    }
                }
                break;
            case 3:
                printf("Select zodiac to update:\n");
                for (int i = 0; i < 12; i++) {
                    printf("%d. %s\n", i+1, zodiacSigns[i].name);
                }
                printf("Enter choice (1-12): ");
                int zChoice;
                scanf("%d", &zChoice);
                while(getchar() != '\n');
                if (zChoice < 1 || zChoice > 12) {
                    printf("Invalid choice.\n");
                } else {
                    updateForecast(&zodiacSigns[zChoice -1]);
                    for (int i = 0; i < userCount; i++) {
                        if (strcmp(users[i].zodiac.name, zodiacSigns[zChoice -1].name) == 0) {
                            strcpy(users[i].zodiac.forecast, zodiacSigns[zChoice -1].forecast);
                        }
                    }
                }
                break;
            case 4:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while(choice != 4);

    return 0;
}
