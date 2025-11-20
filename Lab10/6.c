#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define MAX_NOTES 50

void remove_newline(char *s){size_t len=strlen(s); if(len && s[len-1]=='\n') s[len-1]='\0';}

void add_note(char notes[][101], int *count){if(*count>=MAX_NOTES){printf("Max notes\n"); return;} char temp[101]; printf("Enter note: "); fgets(temp,101,stdin); remove_newline(temp); strcpy(notes[*count],temp); (*count)++;}
void delete_note(char notes[][101], int *count){if(*count==0){printf("No notes\n"); return;} char temp[101]; printf("Note to delete: "); fgets(temp,101,stdin); remove_newline(temp); bool f=false; for(int i=0;i<*count;i++){if(strcmp(notes[i],temp)==0){for(int j=i;j<*count-1;j++) strcpy(notes[j],notes[j+1]); (*count)--; f=true; printf("Deleted\n"); break;}} if(!f) printf("Not found\n");}
void update_note(char notes[][101], int count){if(count==0){printf("No notes\n"); return;} char temp[101]; printf("Note to update: "); fgets(temp,101,stdin); remove_newline(temp); bool f=false; for(int i=0;i<count;i++){if(strcmp(notes[i],temp)==0){printf("Enter new note: "); char newn[101]; fgets(newn,101,stdin); remove_newline(newn); strcpy(notes[i],newn); f=true; break;}} if(!f) printf("Not found\n");}
void search_note(char notes[][101], int count){if(count==0){printf("No notes\n"); return;} char temp[101]; printf("Search phrase: "); fgets(temp,101,stdin); remove_newline(temp); bool f=false; for(int i=0;i<count;i++){if(strstr(notes[i],temp)!=NULL){printf("%s\n",notes[i]); f=true;}} if(!f) printf("No match\n");}

int count_word(char *s, char *word){
    int c=0;
    char *p=s;
    while((p=strstr(p,word))!=NULL){c++; p+=strlen(word);}
    return c;
}

void count_all_words(char notes[][101], int count){
    if(count==0){printf("No notes\n"); return;}
    char word[101]; printf("Enter word to count: "); fgets(word,101,stdin); remove_newline(word);
    int total=0;
    for(int i=0;i<count;i++) total+=count_word(notes[i],word);
    printf("Total occurrences: %d\n", total);
}

int main(){
    char notes[MAX_NOTES][101]; int count=0;
    FILE *fp=fopen("episodes.txt","r");
    if(fp){while(count<MAX_NOTES && fgets(notes[count],101,fp)){remove_newline(notes[count]); count++;} fclose(fp);}
    int input; do{
        printf("1->Add 2->Delete 3->Update 4->Search 5->CountWord -1->Exit: "); scanf("%d",&input); while(getchar()!='\n');
        switch(input){
            case 1: add_note(notes,&count); break;
            case 2: delete_note(notes,&count); break;
            case 3: update_note(notes,count); break;
            case 4: search_note(notes,count); break;
            case 5: count_all_words(notes,count); break;
            case -1: break; default: printf("Invalid\n");
        }
    }while(input!=-1);

    fp=fopen("episodes.txt","w");
    for(int i=0;i<count;i++) fprintf(fp,"%s\n",notes[i]);
    fclose(fp);

    return 0;
}
