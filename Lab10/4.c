#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define MAX_AFF 50

void remove_newline(char *s){size_t len=strlen(s); if(len && s[len-1]=='\n') s[len-1]='\0';}

int main(){
    char aff[MAX_AFF][101]; int count=0;
    FILE *fp=fopen("affirm.txt","r");
    if(fp){while(count<MAX_AFF && fgets(aff[count],101,fp)){remove_newline(aff[count]); count++;} fclose(fp);}

    int input; do{
        printf("1->Add 2->Delete 3->Update 4->Search -1->Exit: ");
        scanf("%d",&input); while(getchar()!='\n');
        switch(input){
            case 1:{if(count>=MAX_AFF){printf("Max reached\n"); break;} char temp[101]; printf("Enter affirmation (<=7 words): "); fgets(temp,101,stdin); remove_newline(temp); strcpy(aff[count++],temp); break;}
            case 2:{if(count==0){printf("Empty\n"); break;} char temp[101]; printf("Enter affirmation to delete: "); fgets(temp,101,stdin); remove_newline(temp); bool f=false; for(int i=0;i<count;i++){if(strcmp(aff[i],temp)==0){for(int j=i;j<count-1;j++) strcpy(aff[j],aff[j+1]); count--; f=true; printf("Deleted\n"); break;}} if(!f) printf("Not found\n"); break;}
            case 3:{if(count==0){printf("Empty\n"); break;} char temp[101]; printf("Enter affirmation to update: "); fgets(temp,101,stdin); remove_newline(temp); bool f=false; for(int i=0;i<count;i++){if(strcmp(aff[i],temp)==0){printf("Enter new affirmation: "); char newa[101]; fgets(newa,101,stdin); remove_newline(newa); strcpy(aff[i],newa); f=true; break;}} if(!f) printf("Not found\n"); break;}
            case 4:{if(count==0){printf("Empty\n"); break;} char temp[101]; printf("Enter phrase to search: "); fgets(temp,101,stdin); remove_newline(temp); bool f=false; for(int i=0;i<count;i++){if(strstr(aff[i],temp)!=NULL){printf("%s\n",aff[i]); f=true;}} if(!f) printf("No match\n"); break;}
            case -1: break; default: printf("Invalid\n");
        }
    }while(input!=-1);

    fp=fopen("affirm.txt","w");
    for(int i=0;i<count;i++) fprintf(fp,"%s\n",aff[i]);
    fclose(fp);

    return 0;
}
