#ifndef CLASS_USER
#define CLASS_USER
#include<stack>
#include<cstring>
#include"./DOB.hpp"
#include "./fileHandling.hpp"
#include "./arrayList.hpp"

class User{
private:
   static int numberOfUser;
   
   long nationalIdCard;
   DOB dob;
   char firstName[45];
   char lastName[45];
   char phoneNumber[12];
   char address[100];

   long bankNumberKHR;
   long bankNumberUSD; //similar to ACLIDA use Phone Number as the Bank number 

   double loanUSD;
   double loanKHR;
   double totalMoneyKHR;
   double totalMoneyUSD;
   char password[16];
   int qrCodePayment; // consider move to dinamic array for many QrCode
public:
   User(){
      strcpy(firstName, "NULL");
      strcpy(lastName, "NULL");
      strcpy(phoneNumber, "NULL");
      strcpy(address, "NULL");
      strcpy(password, "NULL");
      nationalIdCard=0;
      loanKHR=0.00;
      loanUSD=0.00;
      totalMoneyKHR=0.00;
      totalMoneyUSD=0.00;
      qrCodePayment = 0;
      numberOfUser++;
   }
   void input(const string &fileName){
      // string fname;
      cout<<"Create a User Account "<<endl;
      cout<<"User information "<<endl;
      cout<<"First Name : ";cin>>firstName;
      // stringToChar (&firstName,fname);
      // cout<<"Last Name  : ";cin>>lastName;
      // cout<<"National ID Card : ";cin>>nationalIdCard;
      // cin.ignore();
      // cout<<"Address    : ";getline(cin,address);
      // dob.inputDate();
      // cin.ignore();
      cout<<"Security Section "<<endl;
      inputPhoneNumber(fileName);
      // inputPassword();
   }
   char* getPhoneNumber(){
      return phoneNumber;
   }
   void inputPhoneNumber(const string &fileName){
      enterPhonenumber:
      cout<<"Phone Number : ";cin>>phoneNumber;
      //add validation
      if(isPhoneNumberUsed(fileName,phoneNumber)){
         cerr<<"Phone Number has been used "<<endl;
         cerr<<"Enter it again"<<endl;
         goto enterPhonenumber;
      }
   }
   bool isPhoneNumberUsed(const string fileName,const char *phoneNumber){
      //add code
      ArrayList<User> tempUser;
      if((numberOfUser)>0){
         readFromBinary(fileName,tempUser);
         for(int i=0;i<tempUser.getLength();i++){        
            char *phone = tempUser.getValue(i).getPhoneNumber();
            if(strcmp(phoneNumber,phone)==0) return true;
         }
      }
      return false;
   }

   void inputPassword(){
      char confirmPassword[16];
      enterPassword:
      cout<<"Password   : ";cin>>password;
      cout<<"Confirm Password : ";cin>>confirmPassword;
      if(strcmp(confirmPassword,password)!=0){
         cerr<<"Confirm Password Incorrect "<<endl;
         cerr<<"Enter password again"<<endl;
         goto enterPassword;
      }
   }

   void output(){
      cout<<firstName<<" "<<phoneNumber<<endl;
      // cout<<phoneNumber<<" ";
   }
};
#endif
