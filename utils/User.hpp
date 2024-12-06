#ifndef CLASS_USER
#define CLASS_USER
#include<stack>
#include<cstring>
#include<cmath>
#include"./DOB.hpp"
#include "./fileHandling.hpp"
#include "./arrayList.hpp"

class User{
private:
   
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
   }
   void input(const string &fileName){
      // string fname;
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
      inputPassword();
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
      char phone[12];
      if((readFromBinary(fileName,tempUser))){
         for(int i=0;i<tempUser.getLength();i++){        
            strcpy(phone,tempUser.getValue(i).getPhoneNumber());
            if(strcmp(phoneNumber,phone)==0) return true;
         }
      }
      return false;
   }

   void inputPassword(){
      char confirmPassword[16];
      char pass[16];
      enterPassword:
      cout<<"Password   : ";cin>>pass;
      cout<<"Confirm Password : ";cin>>confirmPassword;
      if(strcmp(confirmPassword,pass)!=0){
         cout<<"Confirm Password Incorrect "<<endl;
         cout<<"Enter password again"<<endl;
         goto enterPassword;
      }
      strcpy(password,pass);
   }
   void output(){
      cout<<firstName<<" "<<phoneNumber<<endl;
   }
   void showBalance(){
      cout << "Account Balance:" << endl;
      cout << " - KHR: " << totalMoneyKHR <<"R"<< endl;
      cout << " - USD: " << totalMoneyUSD <<"$"<< endl;
   }
   // bool checkUSDTransfer(double usd){

   // }
   double changeUSDtoKHR(double usd,float exchangeRate){
      usd*=exchangeRate;
      return usd;
   }
   double changeKHRtoUSD(double khr,float exchangeRate){
      khr/=(double)exchangeRate;
      return round(khr*1000.0)/1000.0;
   }
   void transferOwnAccount(float exchangeRate){
      int op;
      double usd;
      double khr;
      cout<<"1 . From USD to KHR "<<endl;
      cout<<"2 . From KHR to USD "<<endl;
      cout<<"0 . Exit"<<endl;
      cout<<"Choose :";cin>>op;
      switch(op){
         case 1:
            cout<<"Amount (USD) : ";cin>>usd;
            //check validation when transfer
            // setTotalMoneyUSD();
            setTotalMoneyKHR(totalMoneyKHR+changeUSDtoKHR(usd,exchangeRate));
            setTotalMoneyUSD(totalMoneyUSD-usd);
            cout<<"Transfer Success";
            //write History
            break;
         case 2:
            cout<<"Amount (KHR) : ";cin>>khr;
            //check validation when transfer
            
            setTotalMoneyKHR(totalMoneyKHR-khr);
            setTotalMoneyUSD(totalMoneyUSD+changeKHRtoUSD(khr,exchangeRate));
            cout<<"Transfer Success";
            //write History
            break;
         case 0:
            exit(2);
            break;
      }
   }












   char* getPhoneNumber() { 
   return phoneNumber; 
   }

   void setPhoneNumber(const char* number) { 
      strncpy(phoneNumber, number, sizeof(phoneNumber) - 1); 
      phoneNumber[sizeof(phoneNumber) - 1] = '\0'; 
   }

   char* getFirstName() { 
      return firstName; 
   }

   void setFirstName(const char* name) { 
      strncpy(firstName, name, sizeof(firstName) - 1); 
      firstName[sizeof(firstName) - 1] = '\0'; 
   }

   char* getLastName() { 
      return lastName; 
   }

   void setLastName(const char* name) { 
      strncpy(lastName, name, sizeof(lastName) - 1); 
      lastName[sizeof(lastName) - 1] = '\0'; 
   }

   char* getAddress() { 
      return address; 
   }

   void setAddress(const char* addr) { 
      strncpy(address, addr, sizeof(address) - 1); 
      address[sizeof(address) - 1] = '\0'; 
   }

   long getNationalIdCard() { 
      return nationalIdCard; 
   }

   void setNationalIdCard(long id) { 
      nationalIdCard = id; 
   }

   long getBankNumberKHR() { 
      return bankNumberKHR; 
   }

   void setBankNumberKHR(long number) { 
      bankNumberKHR = number; 
   }

   long getBankNumberUSD() { 
      return bankNumberUSD; 
   }

   void setBankNumberUSD(long number) { 
      bankNumberUSD = number; 
   }

   double getLoanUSD() { 
      return loanUSD; 
   }

   void setLoanUSD(double loan) { 
      loanUSD = loan; 
   }

   double getLoanKHR() { 
      return loanKHR; 
   }

   void setLoanKHR(double loan) { 
      loanKHR = loan; 
   }

   double getTotalMoneyKHR() { 
      return totalMoneyKHR; 
   }

   void setTotalMoneyKHR(double total) { 
      totalMoneyKHR = total; 
   }

   double getTotalMoneyUSD() { 
      return totalMoneyUSD; 
   }

   void setTotalMoneyUSD(double total) { 
      totalMoneyUSD = total; 
   }

   char* getPassword() { 
      return password; 
   }

   void setPassword(const char* pwd) { 
      strncpy(password, pwd, sizeof(password) - 1); 
      password[sizeof(password) - 1] = '\0'; 
   }

   int getQrCodePayment() { 
      return qrCodePayment; 
   }

   void setQrCodePayment(int code) { 
      qrCodePayment = code; 
   }      
};
#endif
