#include "./utils/User.hpp"
#include "./utils/Bank.hpp"
#include "./utils/ATM.hpp"
#include <unistd.h>
#include <string>
#define DATA_USER "user.dat"
void clearScreen() {
// #ifdef _WIN32
//    system("cls");
// #else
//    system("clear");
// #endif
   system("cls");

}
int displayOption(string *allOption,int size){
   int op;
   for(int i=1;i<=size;i++){
      cout<<i<<" . "<<(allOption[i-1])<<endl;
   }
   cout<<"0 . Exit "<<endl;
   cout<<"Choose : ";cin>>op;
   return op;
}
bool enterPassword(User user){
   int wrong=0;
   char password[16];
   enterPassword:
   cout<<"Enter Passsword : ";cin>>password;
   if(strcmp(password,user.getPassword())==0){
      cout<<"Login Success . . ."<<endl;
      return true;
   }else{
      wrong +=1;
      cout<<"Incorect Password"<<endl;
      sleep(1);
      if(wrong>=3){
         cout<<"Incorect Password to many time"<<endl;
         sleep(1);
         return false;
      }
      goto enterPassword;
   }
}
int main(){

   int option;
   string mainOption[] = {"ATM","User","Administration"};
   string userLoginOption[] = {"Login","Register"};
   string userInterface[] = {"Check Balance", "Transaction History", "Transfer Money", "Payment", 
   "Deposit with Interest", "Apply Loan", "Update Information", "Check Information Detail", "Request to Admin"};
   string transferOption[] = {"Transfer to Own Account","Transfer to Other Account"};
   Bank bank;
   ArrayList<User> users;
   User newUser;
   int currentIndexUser=-1;

   //Load data to use
   readFromBinary(DATA_USER,users);

   do{
      clearScreen();
      cout<<"Welcome To [Bank Name] Please Login "<<endl;
      option = displayOption(mainOption,3);
      switch(option){
         case 1:
            clearScreen();
            cout<<"[Bank Name] ATM "<<endl;
            //process ATm
            break;
         case 2:
            USER:
            clearScreen();
            cout<<"[Bank Name] User Login "<<endl;
            option = displayOption(userLoginOption,2);
            switch(option){
               case 1:
                  char phone[12],password[16];
                  clearScreen();
                  cout<<" Enter Information to Login"<<endl;
                  cout<<"Phone number : ";cin>>phone;
                  currentIndexUser=bank.indexOfUser(phone,users);
                  if(currentIndexUser!=-1){
                     cin.ignore();
                     if(enterPassword(users.getValue(currentIndexUser))){
                        cout<<"Login success ...";
                        //apply some animetion
                        userInterface:
                           clearScreen();
                           cout<<"Welcome back "<<users.getValue(currentIndexUser).getFirstName()<<endl;
                           option = displayOption(userInterface,9);
                           switch(option){
                              //Code
                              case 1:
                                 //Code Show Money of user 
                                 users.getValue(currentIndexUser).showBalance();
                                 break;
                              case 2:
                                 //Code Transaction History
                                 break;
                              case 3:
                                 //Code transfer money ACLIDA Concept
                                 option = displayOption(transferOption,2);
                                 switch(option){
                                    case 1:

                                       break;
                                 }
                                 break;
                              case 4:
                                 //Code payment
                                 break;
                              case 5:
                                 //Code Deposit with Interest
                                 break;
                              case 6:
                                 //Code Apply Loan
                                 break;
                              case 7:
                                 //Code Update Information
                                 break;
                              case 8:
                                 //Code Check Information Detail
                                 break;
                              case 9:
                                 //Code Request to Admin
                                 break;
                              case 0:
                                 goto USER;
                                 break;
                           }
                        goto userInterface;
                     }
                  }else{
                        currentIndexUser = -1;
                        cout<<"User Not Found"<<endl;
                        sleep(1);
                        goto USER;
                     }
                  break;
               case 2:
                  clearScreen();
                  cout<<" Create User Account"<<endl;
                  newUser.input(DATA_USER);
                  users.push(newUser);
                  writeToBinary(DATA_USER,users);
                  break;
               case 0:
                  //exit
                  break;
            }
            break;
         case 3:
            clearScreen();
            cout<<"[Bank Name] Administration "<<endl;
            break;
         case 0:
            clearScreen();
            cout<<"Thank You"<<endl;
            break;
         default:
            cout<<"Invalid Input "<<endl;
            break;
         }
      }while(option!=0);

   return 0;
}