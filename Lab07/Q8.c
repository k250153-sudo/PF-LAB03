#include <stdio.h>
int main(){
    char s1[100],s2[100];
    int i,flag=0;
    printf("Enter first string: ");
    scanf("%s",s1);
    printf("Enter second string: ");
    scanf("%s",s2);
    for(i=0;s1[i]!='\0'||s2[i]!='\0';i++){
        if(s1[i]!=s2[i]){
            flag=1;
            break;
        }
    }
    if(flag==0) printf("Strings are equal\n");
    else printf("Strings are not equal\n");
    return 0;
}

