#ifndef CLASS_USER
#define CLASS_USER
#include<stack>
#include<cstring>
#include<cmath>
#include "./DOB.hpp"
#include "./fileHandling.hpp"
#include "./arrayList.hpp"
#include "QRCode.hpp"
#include <vector>
class User{
private:
   string firstName;
   string lastName;
   DOB dob;
   long nationalIdCard;
   char phoneNumber[16];
   string address;
   double loanUSD;
   double loanKHR;
   double totalMoneyKHR;
   double totalMoneyUSD;
   char password[16];
   vector<QRCode> qrCode;
public:
   // change
  User(const std::string& firstName, 
     const std::string& lastName, 
     const std::string& address, 
     const char* phoneNumber, 
     const char* password, 
     int nationalIdCard, 
     double loanKHR, 
     double loanUSD, 
     double totalMoneyKHR, 
     double totalMoneyUSD) {
    
    this->firstName = firstName;
    this->lastName = lastName;
    this->address = address;
    strcpy(this->phoneNumber, phoneNumber);
    strcpy(this->password, password);
    this->nationalIdCard = nationalIdCard;
    this->loanKHR = loanKHR;
    this->loanUSD = loanUSD;
    this->totalMoneyKHR = totalMoneyKHR;
    this->totalMoneyUSD = totalMoneyUSD;
}

   void displayInfo() {
      cout << "=========================================" << endl;
      cout << "         Users Account Details        " << endl;
      cout << "=========================================" << endl;
      cout << "National ID       : " << nationalIdCard << endl;
      cout << "Name              : " << firstName << " " << lastName << endl;
      cout << "Ddate of Birth    : " << dob.getDOB()<<endl;
      cout << "Phone Number      : " << phoneNumber << endl;
      cout << "Address           : " << address << endl;
      cout << "-----------------------------------------" << endl;
      cout << "         Financial Information           " << endl;
      cout << "-----------------------------------------" << endl;
      cout << fixed << setprecision(2);
      cout << "Loan Amount (USD) : $" << loanUSD << endl;
      cout << "Loan Amount (KHR) : " << loanKHR << " KHR" << endl;
      cout << "Total Balance USD : $" << totalMoneyUSD << endl;
      cout << "Total Balance KHR : " << totalMoneyKHR << " KHR" << endl;
      cout << "=========================================" << endl;
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
   void writeToFile(const string &fileName){
      ofstream writeFile(fileName, ios::app | ios::binary);
      writeString(writeFile,firstName);
      writeString(writeFile,lastName);
      writeFile.write((char *)(&dob), sizeof(DOB));
      writeFile.write((char *)(&nationalIdCard), sizeof(nationalIdCard));
      writeFile.write((char *)(&phoneNumber), sizeof(phoneNumber));
      writeString(writeFile,address);
      writeFile.write((char *)(&loanUSD), sizeof(loanUSD));
      writeFile.write((char *)(&loanKHR), sizeof(loanKHR));
      writeFile.write((char *)(&totalMoneyKHR), sizeof(totalMoneyUSD));
      writeFile.write((char *)(&password), sizeof(password));
      writeArrayList(writeFile,qrCode);
      writeFile.close();
   }
   void readFileBin(ifstream &readFile){
      firstName = readString(readFile);
      lastName = readString(readFile);
      readFile.read((char *)(&dob), sizeof(dob));
      readFile.read((char *)(&nationalIdCard), sizeof(nationalIdCard));
      readFile.read((char *)(&phoneNumber), sizeof(phoneNumber));
      address = readString(readFile);
      readFile.read((char *)(&loanUSD), sizeof(loanUSD));
      readFile.read((char *)(&loanKHR), sizeof(loanKHR));
      readFile.read((char *)(&totalMoneyKHR), sizeof(totalMoneyKHR));
      readFile.read((char *)(&password), sizeof(password));
      readArrayList(readFile,qrCode);
   }
   void inputPhoneNumber(const string &fileName){
      enterPhonenumber:
      cout<<"Phone Number : ";cin>>phoneNumber;
      //add validation
      if(isPhoneNumberUsed(fileName,phoneNumber)){
         cout<<"Check"<<endl;
         cerr<<"Phone Number has been used "<<endl;
         cerr<<"Enter it again"<<endl;
         goto enterPhonenumber;
      }
   }
   bool isPhoneNumberUsed(const string fileName,const char *phoneNumber){
      //add code
      ArrayList<User> tempUser;
      readFromBinary(fileName,tempUser);
      char phone[16];
      for(int i=0;i<tempUser.getLength();i++){        
         strcpy(phone,tempUser.getValue(i).getPhoneNumber());
         if(strcmp(phoneNumber,phone)==0) return true;
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
   bool checkSourceUSD(double usd){
      if(usd<=totalMoneyUSD){
         if(usd <= 0){
            throw runtime_error("Invalid Input\n");
         }else{
            return true;
         }
      }else{
         throw runtime_error("Not Enough Money\n");
         return false;
      }
   }
   bool checkSourceKHR(double khr){
      if(khr<=totalMoneyKHR){
         if(khr <= 0){
            throw runtime_error("Invalid Input\n");
         }else{
            return true;
         }
      }else{
         throw runtime_error("Not Enough Money\n");
         return false;
      }
   }
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
            try{
               checkSourceUSD(usd);
               setTotalMoneyKHR(totalMoneyKHR+changeUSDtoKHR(usd,exchangeRate));
               setTotalMoneyUSD(totalMoneyUSD-usd);
               cout<<"Transfer Success"<<endl;
            }catch(exception &e){
               cerr<<e.what();
            };
            break;
         case 2:
            cout<<"Amount (KHR) : ";cin>>khr;
            //check validation when transfer
            try{
               checkSourceKHR(khr);
               setTotalMoneyKHR(totalMoneyKHR-khr);
               setTotalMoneyUSD(totalMoneyUSD+changeKHRtoUSD(khr,exchangeRate));
               cout<<"Transfer Success"<<endl;
            }catch(exception &e){
               cerr<<e.what();
            };
            break;
         case 0:
            exit(2);
            break;
      }
   }
   bool isUSDAccount(){
      int op;
      cout<<"Choose Account : "<<endl;
      cout<<"1 . USD "<<phoneNumber<<endl;
      cout<<"2 . KHR "<<phoneNumber<<endl;
      // cout<<"0 . Exit"<<endl; we will improve this function to exit 
      cout<<"Choose :";cin>>op;
      if(op == 1) return true;
      return false;
   }
   void transferUSDtoOther(double usd,User &destUser,float exchange){
   try{
      if(isUSDAccount()){
         checkSourceUSD(usd);
         setTotalMoneyUSD(totalMoneyUSD-usd);
         destUser.setTotalMoneyUSD(destUser.getTotalMoneyUSD()+usd);
         cout<<"Transfer Success"<<endl;
         }else{
            checkSourceKHR(changeUSDtoKHR(usd,exchange));
            setTotalMoneyKHR(totalMoneyKHR-changeUSDtoKHR(usd,exchange));
            destUser.setTotalMoneyUSD(destUser.getTotalMoneyUSD()+usd);
            cout<<"Transfer Success"<<endl;
         }
      }catch(exception &e){
         cerr<<e.what();
      };
   }
   void transferKHRtoOther(double khr,User &destUser,float exchange){
   try{
      if(!isUSDAccount()){
         checkSourceKHR(khr);
         setTotalMoneyKHR(totalMoneyKHR-khr);
         destUser.setTotalMoneyKHR(destUser.getTotalMoneyKHR()+khr);
         cout<<"Transfer Success"<<endl;
      }else{
         checkSourceUSD(changeKHRtoUSD(khr,exchange));
         setTotalMoneyUSD(totalMoneyUSD-changeKHRtoUSD(khr,exchange));
         destUser.setTotalMoneyKHR(destUser.getTotalMoneyKHR()+khr);
         cout<<"Transfer Success"<<endl;
      }
   }catch(exception &e){
      cerr<<e.what();
      };
   }
   void transferToOtherAccount(User &destUser,float exchangeRate){
      double usd,khr;
      int op;
      cout<<"Choose Currency"<<endl;
      cout<<"Destination : "<<destUser.getPhoneNumber()<<destUser.getFirstName()<<endl;;
      cout<<"1 . USD "<<endl;
      cout<<"2 . KHR "<<endl;
      cout<<"0 . Exit"<<endl;
      cout<<"Choose : ";cin>>op;
      switch(op){
         case 1:
            cout<<"Amount (USD) : ";cin>>usd;
            //check validation when transfer
            try{
               transferUSDtoOther(usd,destUser,exchangeRate);
            }catch(exception &e){
               cerr<<e.what();
            };
            break;
         case 2:
            cout<<"Amount (KHR) : ";cin>>khr;
            //check validation when transfer
            try{
               transferKHRtoOther(khr,destUser,exchangeRate); 
            }catch(exception &e){
               cerr<<e.what();
            };
            break;
         case 0:
            exit(2);
            break;
      }
   }
   void addQR(){
      QRCode newQR;
      newQR.cratePaymentCode();
      cout<<newQR.getCodeData()<<endl;
      qrCode.push_back(newQR);   
   }
   bool checkQRCode(const int code,int &index){
      for(int i=0;i<qrCode.size();i++){
         if(qrCode.at(i).getCode() != code) {
            index = i;
            return false;     
         }
      }
      return true;
   }
   void payMoney(ArrayList<User> &destUsers,int indexSource){
      //code
      int tempCode=0;
      int indexQRCode=0;
      string confirm;
      bool check=false;
      cout<<"Enter Code : ";cin>>tempCode;
      for(int i = 0; i<destUsers.getLength();i++){
         if(i == indexSource) continue;
         if(destUsers.getValue(i).checkQRCode(tempCode,indexQRCode)){
            check = true;
            cout<<destUsers.getValue(i).getFirstName()<<endl;
            cout<<destUsers.getValue(i).getPhoneNumber()<<endl;
            QRCode& codeToPay = destUsers.getValue(i).getQR().at(i);
            cout<<codeToPay.getCodeData()<<endl;
            cout<<"press Yes/No to pay";cin>>confirm;
            if(confirm == "YES" || confirm =="yes" || confirm =="Yes"){
               cout<<"Process Pay..";
               if(codeToPay.getAmountKHR()!=0){
                  transferKHRtoOther(codeToPay.getAmountKHR(),destUsers.getValue(i),4100);
               }else{
                  transferUSDtoOther(codeToPay.getAmountUSD(),destUsers.getValue(i),4100);
               }
            }
         }
      }
      if(!check){
         cout<<"Code not found"<<endl;
      }
   }
   char* getPhoneNumber() { 
   return phoneNumber; 
   }

   void setPhoneNumber(const char* number) { 
      strncpy(phoneNumber, number, sizeof(phoneNumber) - 1); 
      phoneNumber[sizeof(phoneNumber) - 1] = '\0'; 
   }

   string getFirstName() { 
      return firstName; 
   }

   void setFirstName(const string firstName) { 
      this->firstName = firstName;
   }

   string getLastName() { 
      return lastName; 
   }

   void setLastName(const string lastName) { 
      this->lastName = lastName;
   }

   string getAddress() { 
      return address; 
   }

   void setAddress(const string address) { 
      this->address = address;
   }

   long getNationalIdCard() { 
      return nationalIdCard; 
   }

   void setNationalIdCard(long id) { 
      nationalIdCard = id; 
   }
   string getUserDOB(){
      return dob.getDOB();
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
   vector<QRCode> getQR(){
      return qrCode;
   }   
};
#endif