#include <stdio.h>
#include <string.h>
int main(){
    int a,b,c,d,e;
    char PairPresence = 'N';
    char ThreeOfaKind = 'N';
    printf("The card rank is as follows:\n");
    printf("1.Ace, 2-10 are card numbers,11.Jack, 12.Queen, 13.King\n");
    scanf("%d %d %d %d %d", &a, &b, &c, &d, &e);
    if (a == b || a == c || a == d || a == e || b == c ||
        b == d || b == e || c == d || c == e || d == e){
        PairPresence = 'Y';
        if (a == b && a == c || a == b && a == d || a == b && a == e ||
        a == c && a == d || a == c && a == e || a == d && a == e ||
        b == c && b == d || b == c && b == e || b == d && b == e ||
        c == d && c == e){
            ThreeOfaKind = 'Y';}}
    if (PairPresence == 'Y'&& ThreeOfaKind =='Y'){
        printf("You have a Full House\n");}
    else{
        printf("You do not have a Full House\n");
    }
    return 0;
}