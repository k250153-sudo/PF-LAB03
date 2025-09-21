#include <stdio.h>

int main() {
   char item[20],type[20];
   printf("Menu is:\nFast Food \n .Burger\n .Pizza \n .Sandwich\nDrinks \n .Coke\n .Pepsi\n .Fanta\n\nPlease tell what would you like to order Fast food or drinks: ");
   scanf(" %s",&type);
   printf("Please enter your item:");
   scanf(" %s",&item);
   switch (type[0]) {
      case 'F':
      case 'f':
         switch (item[0]) {
            case 'B':
            case 'b':
               printf("You have ordered burger ");
               break;
            case 'P':
            case 'p':
               printf("You have ordered pizaa ");
               break;
            case 'S':
            case 's':
                 printf("You have ordered sandwich ");
               break;
         default:
               printf("Invalid Fast Food item\n");
         }
         break;
      case 'D':
         case 'd':
         switch (item[0]) {
         case 'C':
         case 'c':
               printf("You have ordered coke ");
                 break;
         case 'P':
         case 'p':
               printf("You have ordered pepsi ");
               break;
         case 'F':
         case 'f':
               printf("You have ordered fanta ");
               break;
          default: printf("Invalid drink\n");

         }
           break;
      default:
         printf("Invalid option selected!\n");
   }
}