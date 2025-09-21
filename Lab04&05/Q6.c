#include <stdio.h>
int main() {
    char shape[20],calc[20];
    float value,len,breath,radius;

    printf("Please enter the shape and what you want to calculate(enter both): ");
    scanf("%s %s",shape,calc);
    printf("You have entered %s and %s \n",shape,calc);
    switch (shape[0]) {
        case 'C':
        case 'c':
            printf("Enter the radius:");
            scanf("%f",&radius);
            switch (calc[0]) {
                case 'A':
                case 'a':
                    value =  3.14*radius*radius;
                    printf("The area is %.2f",value);
                    break;
                case 'P':
                case 'p':
                    value = 2*3.14*radius;
                    printf("The perimeter is %.2f",value);
                    break;
            }
            break;
        case 'R':
        case 'r':
            printf("Enter the length of the rectangle:");
            scanf("%f",&len);
            printf("Enter the breath of the circle:");
            scanf("%f",&breath);
            switch (calc[0]) {
                case 'A':
                case 'a':
                    value =  len*breath;
                    printf("The area is %.2f",value);
                    break;
                case 'P':
                case 'p':
                    value = 2*(len+breath);
                    printf("The perimeter is %.2f",value);
                    break;
            }
            break;
        case 'T':
            case 't':
            printf("Enter the length of the triangle:");
            scanf("%f",&len);
            printf("Enter the height of the triangle:");
            scanf("%f",&breath);
            switch (calc[0]) {
                case 'A':
                case 'a':
                    value =  0.5*len*breath;
                    printf("The area is %.2f",value);
                    break;
                case 'P':
                case 'p':
                    float s1,s2;
                    printf("Enter the value of the remaining sides:");
                    scanf("%f %f",&s1, &s2);
                    value = s1+s2+len;
                    printf("The perimeter is %.2f",value);
                    break;
            }
            break;
    }
}