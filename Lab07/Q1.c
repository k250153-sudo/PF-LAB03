#include <stdio.h>

int main(void) {
    int temps[] = {32, 28, 35, 30, 40, 25, 38};
    int max = temps[0];
    int min = temps[0];
    int lenght = sizeof(temps)/sizeof(temps[0]);
    for(int i = 1; i < lenght; i++) {
        if(temps[i] > max) max = temps[i];
        if(temps[i] < min) min = temps[i];
    }
    printf("Maximum temperature: %d\n", max);
    printf("Minimum temperature: %d\n", min);
    return 0;
}