#include <stdio.h>
#include <stdlib.h>
// 65-90 caps 97-122 small 48-57 digits
// Assuming the pattern string from the questions and using the criteria according to that.
char *readpassword() {
    char *pas=(char *)malloc(sizeof(char)*1);
    if (pas==NULL) {
        printf("Memory Error");
        exit(1);
    }
    int size=1,index=0;
    char c;
    while ((c=getchar()) != '\n') {
        pas[index]=c;
        size++;
        index++;
        char *temp=realloc(pas,size);
        if (temp==NULL) {
            printf("Not enough space");
            free(pas);
            exit(1);
        }
        pas=temp;
    }
    pas[index]='\0';
    return pas;

}

int score(char *pass){
 int score_u=0;
 int score_l=0;
 int score_d=0;
 int score_s=0;
    int score_f=0;

    while (*pass!='\0') {
        if ((*pass >= 65 && *pass <= 90)) {
            score_u++;
        }
        else if (*pass >= 97 && *pass <= 122) {
            score_l++;
        }
        else if (*pass >= 48 && *pass <= 57) {
            score_d++;
        }
        else {
            score_s++;
        }
        pass++;
    }
    if (score_u>0) {
        score_f++;
    }
    if (score_l>0) {
        score_f++;
    }
    if (score_d>1) {
        score_f++;
    }
    if (score_s>1) {
        score_f++;
    }
    return score_f;

}


int main() {
    printf("Enter the number of participants:");
    int n;
    scanf("%d",&n);
    getchar();
    int *similarity=(int *)malloc(n*sizeof(int));
    char **pass=(char**)malloc(n*sizeof(char*));
    if (pass==NULL) {
        printf("Not enough space");
        exit(1);
    }
    for (int i=0;i<n;i++) {
        printf("Enter the password for participant %d: ",i+1);
        *(pass+i)=readpassword();
        *(similarity+i)=score(*(pass+i));
    }
    for (int i=0;i<n;i++) {
        printf("Password for participant %d: %s. Similarity percentage is %.1f%%\n",i+1,*(pass+i),((float)*(similarity+i)/4) * 100);

    }
    int index=0;
    int hightscore=similarity[0];
    for (int i=1;i<n;i++) {
        if (similarity[i]>hightscore) {
            hightscore=similarity[i];
            index=i;
        }
    }
    printf("Password with highest similarity score is %s with similarity score of %.1f%% of participant number %d.",*(pass+index),((float)*(similarity+index)/4) * 100,index+1);
    for (int i=0;i<n;i++) {
        free(pass[i]);
    }
    free(pass);
    free(similarity);
    return 0;

}

