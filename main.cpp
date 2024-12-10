#include "./utils/User.hpp"
#include "./utils/Bank.hpp"
#include "./utils/ATM.hpp"
#include "./utils/Admin.hpp"
#include "./utils/fileHandling.hpp"
#include <unistd.h>
#include <string>
#define DATA_USER "user.dat"

// char* comfirmPassword();
bool enterPassword(User user);
int displayOption(string *allOption,int size);
void header(const string header);
void clearScreen();
int main(){
   int option;
   string mainOption[] = {"ATM","User","Administration"};
   string userLoginOption[] = {"Login","Register"};
   string userInterface[] = {"Check Balance", "Transaction History", "Transfer Money", "Payment", 
   "Deposit with Interest", "Apply Loan", "Update Information", "Check Information Detail", "Request to Admin"};
   string transferOption[] = {"Transfer to Own Account","Transfer to Other Account"};
   Bank bank;
   Admin admin;
   ArrayList<User> users;
   User newUser;
   int currentIndexUser=-1;

   //Load data to use
   bank.setExchnageRate(4100.00);
   do{
      clearScreen();
      // cout<<"Welcome To [Bank Name] Please Login "<<endl;
      START:
      header("KON KHMER BANK");
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
            header("USER INTERFACE");
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
                           header("USER ACCOUNT");
                           cout<<"Welcome back "<<users.getValue(currentIndexUser).getFirstName()<<endl;
                           option = displayOption(userInterface,9);
                           switch(option){
                              //Code
                              case 1:
                                 //Code Show Money of user 
                                 header("USER BALANCE");
                                 users.getValue(currentIndexUser).showBalance();
                                 break;
                              case 2:
                                 header("TRANSACTION HISTORY");
                                 //Code Transaction History
                                 break;
                              case 3:
                                 //Code transfer money ACLIDA Concept
                                 option = displayOption(transferOption,2);
                                 switch(option){
                                    case 1:{
                                       header("TRANSFER TO OWN ACCOUNT");
                                       users.getValue(currentIndexUser).transferOwnAccount(bank.getExchnageRate()); 
                                       // need to write
                                       }
                                    break;
                                    case 2:{
                                        //destination User
                                       char phone[12];
                                       header("TRANSFER TO OTHER ACCOUNT");
                                       cout<<"Phone Number : ";cin>>phone;
                                       User &destUser = users.getValue(bank.indexOfUser(phone,users));
                                       users.getValue(currentIndexUser).transferToOtherAccount(destUser,bank.getExchnageRate());
                                       break;
                                       }
                                    case 0:{
                                       goto userInterface;
                                       break;
                                       }
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
                              case 0:{
                                 goto USER;
                                 break;
                              }
                           }
                        goto USER;
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
                  newUser.setTotalMoneyKHR(100000);
                  newUser.setTotalMoneyUSD(100);
                  newUser.writeToFile(DATA_USER);
                  users.push(newUser);
                  break;
               case 0:
                  //exit
                  goto START;
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

void clearScreen() {
#ifdef _WIN32
   system("cls");
#else
   system("clear");
#endif
}
void header(const string header){
   cout << "=========================================" << endl;
   cout << "         "<<header<<endl;
   cout << "=========================================" << endl<<endl;
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
// char comfirmPassword(char *cpassword) { // export from project term 2 year 1
//    char tempChar[50]="",tempCpass[50]="";
//    static char cpass[50];
//    int ascii,i=0;
//    while(1){
//       tempChar[i]=getch();
//       ascii=tempChar[i];
//       if(ascii==13){
//          break; 
//       }else if((ascii==8) && (i>=0)){
//          printf("\b \b");
//          tempCpass[i]=tempCpass[i+1];
//          i--;
//       }else{
//          printf("*");
//          strcpy(tempCpass,tempChar);
//          i++;
//       }
//    }

// } implement next time
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