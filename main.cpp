#include "./utils/User.hpp"
#include "./utils/Bank.hpp"
// #include "./utils/ATM.hpp"
#include "./utils/Admin.hpp"
#include "./utils/fileHandling.hpp"
#include <unistd.h>
#include <string>
#include <cstdlib>
#define DATA_USER "./Data/usr.dat"

// char* comfirmPassword();
bool enterPassword(User user);
int displayOption(string *allOption,int size);
void header(const string header);
void clearScreen();
void puseScreen();
int main(){
   int option;
   string mainOption[] = {"ATM","User","Administration"};
   string userLoginOption[] = {"Login","Register"};
   string userInterface[] = {"Check Balance", "Transaction History", "Transfer Money", "Payment", 
   "Deposit with Interest", "Loan", "Update Information", "Check Information Detail", "Request to Admin"};
   string transferOption[] = {"Transfer to Own Account","Transfer to Other Account"};
   Bank bank;
   Admin admin;
   ArrayList<User> users;
   User newUser;
   int currentIndexUser=-1;

   //Load data to use
   bank.setExchnageRate(4100.00);
   readFromBinary(DATA_USER,users);
   do{
      clearScreen();
      START:
      header("KON KHMER BANK");
      option = displayOption(mainOption,3);
      switch(option){
         case 1:
            clearScreen();
            // //atm
            // ATM atm;
            // atm.displayMenu():
            // return 0;
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
                  currentIndexUser=indexOfUser(phone,users);
                  if(currentIndexUser!=-1){
                     cin.ignore();
                     if(enterPassword(users.getValue(currentIndexUser))){
                        cout<<"Login success ..."<<endl;
                        //apply some animetion
                        userInterface:
                           clearScreen();
                           header("USER ACCOUNT");
                           int op;
                           cout<<"Welcome back "<<users.getValue(currentIndexUser).getFirstName()<<endl;
                           op = displayOption(userInterface,9);
                           switch(op){
                              //Code
                              case 1:{
                                 //Code Show Money of user 
                                 clearScreen();
                                 header("USER BALANCE");
                                 users.getValue(currentIndexUser).showBalance();
                                 puseScreen();
                                 break;
                                 
                                 }
                              case 2:
                                 clearScreen();
                                 header("TRANSACTION HISTORY");
                                 //Code Transaction History
                                 puseScreen();
                                 break;
                              case 3:
                                 //Code transfer money ACLIDA Concept
                                 clearScreen();
                                 header("TRANSFER MONEY");
                                 switch(displayOption(transferOption,2)){
                                    case 1:{
                                       clearScreen();
                                       header("TRANSFER TO OWN ACCOUNT");
                                       users.getValue(currentIndexUser).transferOwnAccount(bank.getExchnageRate()); 
                                       // need to write
                                       }
                                    break;
                                    case 2:{
                                        //destination User
                                       clearScreen();
                                       header("TRANSFER TO OTHER ACCOUNT");
                                       char phone[12];
                                       cout<<"Phone Number : ";cin>>phone;
                                       User &destUser = users.getValue(indexOfUser(phone,users));
                                       users.getValue(currentIndexUser).transferToOtherAccount(destUser,bank.getExchnageRate());
                                       writeToBinary(DATA_USER,users);
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
                                 clearScreen();
                                 header("PAYMENT TRANSACTION");
                                 break;
                              case 5:
                                 //Code Deposit with Interest
                                 clearScreen();
                                 header("DEPOSIT WITH INTEREST");
                                 break;
                              case 6:
                                 //Code Apply Loan
                                 clearScreen();
                                 header("APPLY FOR LOAN");
                                 break;
                              case 7:
                                 clearScreen();
                                 header("UPDATE USER INFORMATION ");
                                 //Code Update Information
                                 users.getValue(currentIndexUser).updateUserInfo();
                                 writeToBinary(DATA_USER,users);
                                 break;
                              case 8:
                                 //Code Check Information Detail
                                 clearScreen();
                                 users.getValue(currentIndexUser).displayInfo();
                                 cin.ignore();
                                 break;
                              case 9:{
                                 //Code Request to Admin
                                 string request;
                                 cin.ignore();
                                 header("SENT REQUEST ");
                                 cout<<"Enter Request : ";getline(cin,request);
                                 admin.addRequest(users.getValue(currentIndexUser),request);
                                 admin.showRequest();
                                 //ned to sacve to admin
                                 break;
                                 }
                              case 0:{
                                 goto USER;
                                 break;
                              }
                           }
                           puseScreen();
                        goto userInterface;
                     }
                  }else{
                        currentIndexUser = -1;
                        cout<<"User Not Found"<<endl;
                        sleep(1);
                        goto USER;
                     }
                  break;
               case 2:{
                  clearScreen();
                  cout<<" Create User Account"<<endl;
                  newUser.input(DATA_USER);
                  newUser.setTotalMoneyKHR(100000);
                  newUser.setTotalMoneyUSD(100);
                  // newUser.writeToFile(DATA_USER);
                  if(users.getLength()>0){
                     try{
                        if(newUser.findFreeOrder(users,newUser) == users.getLength()){
                           users.push(newUser);
                        }else{
                           users.insertAt(newUser.findFreeOrder(users,newUser),newUser);
                        }
                     }catch(exception &e){
                        cerr<<e.what();
                     }
                  }else{
                     users.push(newUser);
                  }
                  writeToBinary(DATA_USER,users);
                  cout<<"Success ... press any key"<<endl;
                  puseScreen();
                  break;
               }
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
         cin.ignore();
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
void puseScreen() {
#ifdef _WIN32
   system("pause");
#else
   fflush(stdout); // Ensure the message is printed before waiting for input
   getchar();
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