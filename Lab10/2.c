#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LEVELS 50  // adjust as needed

void remove_newline(char *str) {
    size_t len = strlen(str);
    if (len && str[len-1]=='\n') str[len-1]='\0';
}

int main() {
    char levels[MAX_LEVELS][101];
    int count = 0;
    
    FILE *fp = fopen("levels.txt", "r");
    if (fp) {
        while (count < MAX_LEVELS && fgets(levels[count], 101, fp)) {
            remove_newline(levels[count]);
            count++;
        }
        fclose(fp);
    }

    int input;
    do {
        printf("1->Add 2->Delete 3->Update 4->Search -1->Exit: ");
        scanf("%d", &input);
        while(getchar()!='\n');

        switch(input) {
            case 1: {
                if(count >= MAX_LEVELS){printf("Max levels reached\n"); break;}
                printf("Enter level description (max 7 words): ");
                char temp[101];
                fgets(temp,101,stdin); remove_newline(temp);
                strcpy(levels[count++], temp);
                break;
            }
            case 2: {
                if(count==0){printf("No levels to delete\n"); break;}
                printf("Enter level to delete: ");
                char temp[101]; fgets(temp,101,stdin); remove_newline(temp);
                bool found=false;
                for(int i=0;i<count;i++){
                    if(strcmp(levels[i], temp)==0){
                        for(int j=i;j<count-1;j++) strcpy(levels[j], levels[j+1]);
                        count--; found=true; printf("Deleted successfully\n"); break;
                    }
                }
                if(!found) printf("Level not found\n");
                break;
            }
            case 3: {
                if(count==0){printf("No levels to update\n"); break;}
                printf("Enter level to update: ");
                char temp[101]; fgets(temp,101,stdin); remove_newline(temp);
                bool found=false;
                for(int i=0;i<count;i++){
                    if(strcmp(levels[i], temp)==0){
                        printf("Enter new description: ");
                        char newdesc[101]; fgets(newdesc,101,stdin); remove_newline(newdesc);
                        strcpy(levels[i], newdesc); found=true; break;
                    }
                }
                if(!found) printf("Level not found\n");
                break;
            }
            case 4: {
                if(count==0){printf("No levels to search\n"); break;}
                printf("Enter phrase to search: ");
                char temp[101]; fgets(temp,101,stdin); remove_newline(temp);
                bool found=false;
                for(int i=0;i<count;i++){
                    if(strstr(levels[i], temp)!=NULL){
                        printf("Found: %s\n", levels[i]); found=true;
                    }
                }
                if(!found) printf("No match found\n");
                break;
            }
            case -1: break;
            default: printf("Invalid option\n");
        }
    } while(input!=-1);

    fp=fopen("levels.txt","w");
    for(int i=0;i<count;i++) fprintf(fp,"%s\n",levels[i]);
    fclose(fp);

    return 0;
}
