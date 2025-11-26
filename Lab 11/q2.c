#include <stdio.h>
#include <string.h>

void countdown(int days, char name[]) {
    if (days == 0) return;
    if (days == 1) {
        printf("1 day left in the %s.\n", name); // Singular for the last day
    } else {
        printf("%d days left in the %s\n", days, name);
    }
    countdown(days - 1, name);
}

struct event {
    int totaldays;
    char name[50];
};

int main() {
    printf("Enter total number of events: ");
    int n;
    scanf("%d", &n);
    getchar();

    struct event events[n];

    for (int i = 0; i < n; i++) {
        printf("Enter the name of event %d: ", i + 1);
        fgets(events[i].name, sizeof(events[i].name), stdin);
        events[i].name[strcspn(events[i].name, "\n")] = 0;

        printf("Enter the total days remaining of %s: ", events[i].name);
        scanf("%d", &events[i].totaldays);
        getchar();
    }

    printf("\nThe countdown of your events:\n");
    for (int i = 0; i < n; i++) {
        countdown(events[i].totaldays, events[i].name);
        printf("\n");
    }

    return 0;
}