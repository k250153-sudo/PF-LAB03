#include <stdio.h>
int main(){
    int Num[10] = {0};
    int i,j;
    printf("Please enter a number between 0-9:\n");
    scanf("%d",&i);
    while (i>=0 && i<10){
        for (j=0;j<10;j++){
            if (j == i){
                Num[j] = Num[j]+1;
                printf("Please enter a number between 0-9:\n");
                scanf("%d",&i);
                break;}}
    }
    printf("Number              Number of Occurences\n");
    for(i=0;i<10;i++){
        printf("%d                   %d\n",i,Num[i]);}
    return 0;
}