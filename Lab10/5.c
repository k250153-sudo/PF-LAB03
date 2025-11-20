#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define MAX_TAGS 50

void remove_newline(char *s){size_t len=strlen(s); if(len && s[len-1]=='\n') s[len-1]='\0';}

void add_tag(char (*tags)[101], int *count){
    if(*count>=MAX_TAGS){printf("Max tags reached\n"); return;}
    char temp[101]; printf("Enter tag: "); fgets(temp,101,stdin); remove_newline(temp);
    strcpy(tags[*count], temp); (*count)++;
}

void delete_tag(char (*tags)[101], int *count){
    if(*count==0){printf("No tags\n"); return;}
    char temp[101]; printf("Enter tag to delete: "); fgets(temp,101,stdin); remove_newline(temp);
    bool f=false; for(int i=0;i<*count;i++){if(strcmp(tags[i],temp)==0){for(int j=i;j<*count-1;j++) strcpy(tags[j],tags[j+1]); (*count)--; f=true; printf("Deleted\n"); break;}} if(!f) printf("Not found\n");
}

void update_tag(char (*tags)[101], int count){
    if(count==0){printf("No tags\n"); return;}
    char temp[101]; printf("Enter tag to update: "); fgets(temp,101,stdin); remove_newline(temp);
    bool f=false; for(int i=0;i<count;i++){if(strcmp(tags[i],temp)==0){printf("Enter new tag: "); char newt[101]; fgets(newt,101,stdin); remove_newline(newt); strcpy(tags[i],newt); f=true; break;}} if(!f) printf("Not found\n");
}

void search_tag(char (*tags)[101], int count){
    if(count==0){printf("No tags\n"); return;}
    char temp[101]; printf("Enter phrase to search: "); fgets(temp,101,stdin); remove_newline(temp);
    bool f=false; for(int i=0;i<count;i++){if(strstr(tags[i],temp)!=NULL){printf("%s\n",tags[i]); f=true;}} if(!f) printf("No match\n");
}

int main(){
    char tags[MAX_TAGS][101]; int count=0;
    FILE *fp=fopen("tags.txt","r");
    if(fp){while(count<MAX_TAGS && fgets(tags[count],101,fp)){remove_newline(tags[count]); count++;} fclose(fp);}
    int input; do{
        printf("1->Add 2->Delete 3->Update 4->Search -1->Exit: "); scanf("%d",&input); while(getchar()!='\n');
        switch(input){
            case 1: add_tag(tags,&count); break;
            case 2: delete_tag(tags,&count); break;
            case 3: update_tag(tags,count); break;
            case 4: search_tag(tags,count); break;
            case -1: break; default: printf("Invalid\n");
        }
    }while(input!=-1);

    fp=fopen("tags.txt","w");
    for(int i=0;i<count;i++) fprintf(fp,"%s\n",tags[i]);
    fclose(fp);
    return 0;
}
