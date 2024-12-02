#include "./utils/User.hpp"
#include "./utils/Bank.hpp"
#include "./utils/ATM.hpp"
int main(){
   bool out=true;
   int choice;
   User user;
   
   do
   {
      cout<<"Welcome to our bank !"<<endl;
      cout<<"Press the number to enter!"<<endl;
      cout<<"1./ User "<<endl;
      cout<<"2./ Admin"<<endl;
      cout<<"3./ ATM"<<endl;
      cout<<"Your choice : ";cin>>choice;
      switch (choice)
      {
      case 1:
         cout<<"user"<<endl;
         cout<<"creat account"<<endl;
         cout<<"login "<<endl;
         break;
      case 2:
         cout<<"admin"<<endl;
         cout<<"login "<<endl;

         break;
      case 3:
         cout<<"ATM"<<endl;
         cout<<"login "<<endl;
         break;

      
      default:
      cout<<"Please try again"<<endl;
         break;
      }

      
   } while (out);
   
   
   return 0;
}