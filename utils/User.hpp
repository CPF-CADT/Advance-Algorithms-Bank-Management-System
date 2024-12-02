#ifndef CLASS_USER
#define CLASS_USER
#include<stack>
#include<vector>
#include"./DOB.hpp"
class User{
private:
   // static int numberUser; cout number of user when constructor create
   long national_id_card;
   DOB dob;
   string firstName;
   string lastName;
   string address;
   int phoneNumber;
   double userId;

   long bankNumberKHR;
   long bankNumberUSD;
   double loanUSD;
   double loanKHR;
   double totalMoneyKHR;
   double totalMoneyUSD;

   stack<string> history; //when read move from stack to queue and finish move to stack
   // vector<string> readHistory; // need to consider mroe Linklist or array list
   string password;
   string username;
   int qrCodePayment; // consider move to dinamic array for many QrCode
public:
   User(){
      national_id_card=0;
      firstName=lastName=address="NULL";
      loanKHR=loanUSD=totalMoneyKHR=totalMoneyUSD=0;
      qrCodePayment = 0;
   }
   void input(){
      cout<<"Create a User Account "<<endl;
      cout<<"User information "<<endl;
      cout<<"First Name : ";cin>>firstName;
      cout<<"Last Name  : ";cin>>lastName;
      cin.ignore();
      cout<<"Address    : ";getline(cin,address);
      cout<<"Phone NUmber : ";cin>>phoneNumber;
      dob.inputDate();
      cin.ignore();
      //this process need to improve algorithm more ;
      cout<<"Username   : ";cin>>username;
      cout<<"Password   : ";cin>>password;

      //and generate the bank id for user after complete password
      //store data to the data base CSV or SQL (consider process)
   }
   long getBankNumberKHR(){
      return bankNumberKHR;
   }
   long getBankNumberUSD(){
      return bankNumberUSD;
   }
};
#endif
