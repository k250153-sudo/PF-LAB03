#include <stdio.h>
int main(){
    printf("Please enter the x cordinate of the point:\n");
    float x;
    scanf("%f",&x);
    printf("Please enter the y cordinate of the point:\n");
    float y;
    scanf("%f",&y);
    if (x>0 && y>0){
        printf("The point %.2f,%.2f lies in the First Quadrant\n",x,y);}
    else if (x<0 && y>0){
        printf("The point %.2f,%.2f lies in the second quadrant\n",x,y);}
    else if (x<0 && y<0){
        printf("The point %.2f,%.2f lies in the third quadrant\n",x,y);}
    else if (x>0 && y<0){
        printf("The point %.2f,%.2f lies in the fourth quadrant\n",x,y);}
    else if (x==0 && y!=0){
        printf("The point %.2f,%.2f lies on the Y axis\n",x,y);}
    else if (y==0 && x!=0){
        printf("The point %.2f,%.2f lies on the X axis\n",x,y);}
    else{
        printf("The point %.2f,%.2f lies at the origin\n",x,y);
    }
    return 0;
}