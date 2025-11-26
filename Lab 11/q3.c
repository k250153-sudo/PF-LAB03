#include <stdio.h>
#include <string.h>

struct employee {
    char name[20];
    int id;
    int present;
};
int totalPresents(struct employee emp[], int n,int threshold) {
    if (n == 0) return 0;

    if (emp[n-1].present < threshold) {
        printf("%s has less than %d present days!\n", emp[n-1].name, threshold);
    }

    return emp[n-1].present + totalPresents(emp, n-1, threshold);
}
int main() {
    printf("Enter total employees: ");
    int n;
    scanf("%d",&n);
    getchar();
    struct employee emp[n];
    for (int i = 0; i < n; i++) {
        printf("Enter name of employee no. %d : ",i+1);
        fgets(emp[i].name, sizeof(emp[i].name), stdin);
        emp[i].name[strcspn(emp[i].name, "\n")] = 0;
        printf("Enter the id of %s: ",emp[i].name);
        scanf("%d",&emp[i].id);
        printf("Enter the number of days %s was present: ",emp[i].name);
        scanf("%d",&emp[i].present);
        getchar();
    }
    printf("Enter minimum requirment of present days: ");
    int threshold;
    scanf("%d",&threshold);
    int total = totalPresents(emp, n,threshold);
    printf("Total present days of all employees: %d\n",total);

}