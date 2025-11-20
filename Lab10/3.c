#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_RECIPES 40

void remove_newline(char *s){size_t len=strlen(s); if(len && s[len-1]=='\n') s[len-1]='\0';}

int main(){
    char recipes[MAX_RECIPES][101]; int count=0;
    FILE *fp=fopen("recipes.txt","r");
    if(fp){
        while(count<MAX_RECIPES && fgets(recipes[count],101,fp)){
            remove_newline(recipes[count]); count++;
        }
        fclose(fp);
    }

    int input;
    do{
        printf("1->Add 2->Delete 3->Update 4->Search -1->Exit: ");
        scanf("%d",&input); while(getchar()!='\n');
        switch(input){
            case 1:{
                if(count>=MAX_RECIPES){printf("Max recipes reached\n"); break;}
                printf("Enter recipe name: "); char temp[101]; fgets(temp,101,stdin); remove_newline(temp);
                strcpy(recipes[count++],temp); break;
            }
            case 2:{
                if(count==0){printf("No recipes to delete\n"); break;}
                printf("Enter recipe to delete: "); char temp[101]; fgets(temp,101,stdin); remove_newline(temp);
                bool found=false;
                for(int i=0;i<count;i++){if(strcmp(recipes[i],temp)==0){
                    for(int j=i;j<count-1;j++) strcpy(recipes[j],recipes[j+1]);
                    count--; found=true; printf("Deleted\n"); break;
                }}
                if(!found) printf("Recipe not found\n"); break;
            }
            case 3:{
                if(count==0){printf("No recipes to update\n"); break;}
                printf("Enter recipe to update: "); char temp[101]; fgets(temp,101,stdin); remove_newline(temp);
                bool found=false;
                for(int i=0;i<count;i++){if(strcmp(recipes[i],temp)==0){
                    printf("Enter new name: "); char newr[101]; fgets(newr,101,stdin); remove_newline(newr);
                    strcpy(recipes[i],newr); found=true; break;
                }}
                if(!found) printf("Recipe not found\n"); break;
            }
            case 4:{
                if(count==0){printf("No recipes to search\n"); break;}
                printf("Enter phrase to search: "); char temp[101]; fgets(temp,101,stdin); remove_newline(temp);
                bool found=false;
                for(int i=0;i<count;i++){if(strstr(recipes[i],temp)!=NULL){printf("%s\n",recipes[i]); found=true;}}
                if(!found) printf("No match\n"); break;
            }
            case -1: break; default: printf("Invalid option\n");
        }
    }while(input!=-1);

    // Sort alphabetically
    for(int x=0;x<count-1;x++){
        for(int y=0;y<count-x-1;y++){
            if(strcmp(recipes[y],recipes[y+1])>0){
                char temp[101]; strcpy(temp,recipes[y]); strcpy(recipes[y],recipes[y+1]); strcpy(recipes[y+1],temp);
            }
        }
    }

    fp=fopen("recipes.txt","w");
    for(int i=0;i<count;i++) fprintf(fp,"%s\n",recipes[i]);
    fclose(fp);

    return 0;
}
