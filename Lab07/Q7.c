#include <stdio.h>
#include <ctype.h>
int main(){
    char str[100];
    int i,v=0,c=0;
    printf("Enter a word: ");
    scanf(" %[^\n]",str);
    for(i=0;str[i]!='\0';i++){
        char ch=tolower(str[i]);
        if(ch>='a'&&ch<='z'){
            if(ch=='a'||ch=='e'||ch=='i'||ch=='o'||ch=='u') v++;
            else c++;
        }
    }
    printf("Vowels = %d\nConsonants = %d\n",v,c);
    return 0;
}
