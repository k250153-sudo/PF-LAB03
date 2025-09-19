#include<stdio.h>
#include <string.h>
int main(){
    int TransactionLimit,Spending1,Spending2,Spending3,Spending4;
    int DailySpendingLimit;
    int Time1,Time2,Time3,Time4;
    char country1[7],country2[7],TCountry1[7],TCountry2[7],TCountry3[7],TCountry4[7];
    char TransactionID1[20];
    char  TransactionID2[20];
    char  TransactionID3[20];
    char TransactionID4[20];
    printf("Hi Welcome to the banking system\n");
    printf("Please enter your daily spending limit:\n");
    scanf("%d",&DailySpendingLimit);
    printf("Please enter the names of the countries you usually transact in:\n");
    scanf("%s %s",country1,country2);// Here we enter the list of countries we normally transact in
    printf("Please enter all your transactions today, in the format:\n");
    printf("<Spending Amount> <Transaction ID> <Time of Transaction in 24hr format e.g:1605 represents 16:05> <Country of Transaction>\n");
    scanf("%d %s %d %s %d %s %d %s %d %s %d %s %d %s %d %s",&Spending1,TransactionID1,&Time1,TCountry1,
        &Spending2,TransactionID2,&Time2,TCountry2,&Spending3,TransactionID3,&Time3,TCountry3
        ,&Spending4,TransactionID4,&Time4,TCountry4);//Here we assume that 4 transaction are made at least
    if (Spending1 > DailySpendingLimit) {// now we check which transaction is suspicious and takes us above the exceeding limit
    printf("Transaction 1 with ID %s is Suspicious due to exceeding limit\n", TransactionID1);}
    else if (Spending1 + Spending2 > DailySpendingLimit) {
        printf("Transaction 2 with ID %s is Suspicious due to exceeding limit\n", TransactionID2);}
    else if (Spending1 + Spending2 + Spending3 > DailySpendingLimit) {
    printf("Transaction 3 with ID %s is Suspicious due to exceeeding limit\n", TransactionID3);}
    else if (Spending1 + Spending2 + Spending3 + Spending4 > DailySpendingLimit) {
    printf("Transaction 4 with ID %s is Suspicious due to exceeding limit\n", TransactionID4);}
    else {
    printf("All transactions are within the daily spending limit\n");}
    if (strcmp(TCountry1, country1) != 0 && strcmp(TCountry1, country2) != 0){//Here we check which transaction is in a different ountry and is flagged suspicious
    printf("Transaction 1 with ID %s is Suspicious due to a different country\n", TransactionID1);}
    if (TCountry2 != country1 && TCountry2 != country2) {
    printf("Transaction 2 with ID %s is Suspicious due to a different country\n", TransactionID2);}
    if (TCountry3 != country1 && TCountry3 != country2) {
    printf("Transaction 3 with ID %s is Suspicious due to a different country\n", TransactionID3);}
    if (TCountry4 != country1 && TCountry4 != country2) {
    printf("Transaction 4 with ID %s is Suspicious due to a different country\n", TransactionID4);}
    if (Time2-Time1<100 || Time3-Time2<100 || Time4-Time3<100){// assume 2 tansaction within hours is suspicious
        printf("Transactions are suspicious due to short time interval\n");}
    return 0;
}