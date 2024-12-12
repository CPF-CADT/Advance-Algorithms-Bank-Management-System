#ifndef CLASS_USER
#define CLASS_USER
#include<cstring>
#include<cmath>
#include "./DOB.hpp"
#include "./fileHandling.hpp"
#include "./arrayList.hpp"
#include "QRCode.hpp"
#include <vector>
#include<iostream>
#include<fstream>
#include<sstream>
#include "./Bank.hpp"
#include "./DepositWithInterest.hpp"
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
   vector<DepositInterest> deposit;
   char password[16];
   vector<QRCode> qrCode;
   vector<string> transactionHistory;
public:
   // change
   User(){
      firstName = "NULL";
      lastName = "NULL";
      address = "NULL";
      strcpy(phoneNumber, "NULL");
      strcpy(password, "NULL");
      nationalIdCard=0;
      loanKHR=0.00;
      loanUSD=0.00;
      totalMoneyKHR=0.00;
      totalMoneyUSD=0.00;
   }

  User(const string& firstName, 
     const string& lastName, 
     const string& address, 
     string dob,
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
    DOB nDob(dob);
    this->dob = nDob;
    strcpy(this->phoneNumber, phoneNumber);
    strcpy(this->password, password);
    this->nationalIdCard = nationalIdCard;
    this->loanKHR = loanKHR;
    this->loanUSD = loanUSD;
    this->totalMoneyKHR = totalMoneyKHR;
    this->totalMoneyUSD = totalMoneyUSD;
}
//   User( const string &firstName,double loanUSD): firstName(firstName),loanUSD(loanUSD){} plan B

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
      cout<<"User information "<<endl;
      cout<<"First Name : ";cin>>firstName;
      // cout<<"Last Name  : ";cin>>lastName;
      // cout<<"National ID Card : ";cin>>nationalIdCard;
      // cin.ignore();
      // cout<<"Address    : ";getline(cin,address);
      // dob.inputDate();
      // cin.ignore();
      cout<<"Security Section "<<endl;
      inputPhoneNumber(fileName);
      inputPassword();

      // cout << "=========================================" << endl;
      // cout << "          User Information Form          " << endl;
      // cout << "=========================================" << endl;
      // cout << "Please enter the following details:" << endl;
      // cout << "First Name       : "; cin >> firstName;
      // cout << "Last Name        : "; cin >> lastName;
      // cout << "National ID      : "; cin >> nationalIdCard;
      // dob.inputDate();
      // cin.ignore(); 
      // cout << "Address          : "; getline(cin, address);
      // cout << "\n=========================================" << endl;
      // cout << "          Security Section               " << endl;
      // cout << "=========================================" << endl;
      // inputPhoneNumber(fileName);
      // inputPassword();
      // cout << "\n=========================================" << endl;
      // cout << "Thank you, " << firstName << " " << lastName << "! Your details have been recorded." << endl;
      // cout << "=========================================" << endl;
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
      writeFile.write((char *)(&totalMoneyKHR), sizeof(totalMoneyKHR));
      writeFile.write((char *)(&totalMoneyUSD), sizeof(totalMoneyUSD));
      writeVector(writeFile,deposit);
      writeFile.write((char *)(&password), sizeof(password));
      writeVector(writeFile,qrCode);
      writeVectorStr(writeFile,transactionHistory);
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
      readFile.read((char *)(&totalMoneyUSD), sizeof(totalMoneyUSD));
      readVector(readFile,deposit);
      readFile.read((char *)(&password), sizeof(password));
      readVector(readFile,qrCode);
      readVectorStr(readFile,transactionHistory);
   }
   void inputPhoneNumber(const string &fileName){
      enterPhonenumber:
      cout<<"Phone Number     : ";cin>>phoneNumber;
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
      cout<<"Create  Password : ";cin>>pass;
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
   void transferToOtherAccount(User &destUser,float exchangeRate){
      double usd,khr;
      int op;
      cout<<"Choose Currency"<<endl;
      cout<<"Destination : "<<destUser.getPhoneNumber()<<destUser.getFirstName()<<endl;
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
            transactionHistory.push_back(logTransactionTransfer(usd,destUser.getName(),phoneNumber,true));
            destUser.addHistoryTransaction(logTransactionReceive(usd,getName(),destUser.getPhoneNumber(),true));
            cout<<"Transfer Success"<<endl;
         }else{
            checkSourceKHR(changeUSDtoKHR(usd,exchange));
            setTotalMoneyKHR(totalMoneyKHR-changeUSDtoKHR(usd,exchange));
            destUser.setTotalMoneyUSD(destUser.getTotalMoneyUSD()+usd);
            transactionHistory.push_back(logTransactionTransfer(usd,destUser.getName(),phoneNumber,false));
            destUser.addHistoryTransaction(logTransactionReceive(usd,getName(),destUser.getPhoneNumber(),false));
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
            transactionHistory.push_back(logTransactionTransfer(khr,destUser.getName(),phoneNumber,false));
            destUser.addHistoryTransaction(logTransactionReceive(khr,getName(),destUser.getPhoneNumber(),false));
            cout<<"Transfer Success"<<endl;
         }else{
            checkSourceUSD(changeKHRtoUSD(khr,exchange));
            setTotalMoneyUSD(totalMoneyUSD-changeKHRtoUSD(khr,exchange));
            destUser.setTotalMoneyKHR(destUser.getTotalMoneyKHR()+khr);
            transactionHistory.push_back(logTransactionTransfer(khr,destUser.getName(),phoneNumber,true));
            destUser.addHistoryTransaction(logTransactionReceive(khr,getName(),destUser.getPhoneNumber(),true));
            cout<<"Transfer Success"<<endl;
         }
      }catch(exception &e){
         cerr<<e.what();
         };
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

   string getName(){
      return firstName +" "+ lastName;
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
   void addHistoryTransaction(string text){
      transactionHistory.push_back(text);
   }
   vector<string> &getHistoryTransaction(){
      return transactionHistory;
   }
   vector<QRCode> getQR(){
      return qrCode;
   }
   string logTransactionTransfer(double amount, const string destName, char* phone,bool usd){
      if(usd){
         return "A cash amount of " + to_string(amount) + "$"+ " was transferred to " + destName + " from account " + phone + ".\n";   
      }else{
         return "A cash amount of " + to_string(amount) +"R"+ " was transferred to " + destName + " from account " + phone + ".\n";   
      }
   }
   string logTransactionReceive(double amount, const string& source, const char* phone,bool usd) {
      if(usd){
         return "A cash amount of " + to_string(amount) +"$"+ " was received by " + source + " from phone number " + string(phone) + ".\n";
      }else{
         return "A cash amount of " + to_string(amount) +"R"+ " was received by " + source + " from phone number " + string(phone) + ".\n";
      }
   }

   
   int findFreeOrder(ArrayList<User> &users, User newUser) {
      int length = users.getLength();
      char phone[12];
      strcpy(phone, newUser.getPhoneNumber()); 
      int lowIndex = 0, mid;
      int highIndex = length - 1;
      if(strcmp(phone, users.getValue(length-1).getPhoneNumber())>0) return length;
      if(strcmp(phone, users.getValue(0).getPhoneNumber())<0) return 0;
      while (lowIndex <= highIndex) {
         mid = lowIndex + (highIndex - lowIndex) / 2;
         if (strcmp(phone,users.getValue(mid).getPhoneNumber())>=0 &&(mid==length-1||strcmp(phone,users.getValue(mid+1).getPhoneNumber())<0) ){
               return mid+1;
         } else if (strcmp(phone, users.getValue(mid).getPhoneNumber())>0) {
               lowIndex = mid + 1;
         } else {
               highIndex = mid - 1;
         }
      }
      return lowIndex;
   }
   int findFreeOrder(vector<User> &users, User newUser) {
      int length = users.size();
      const char* phone = newUser.getPhoneNumber(); // Access the phone number as a C-style string
      int lowIndex = 0, highIndex = length - 1, mid;

    // Handle edge cases
      if (strcmp(phone, users[0].getPhoneNumber()) < 0) {
         return 0; // New phone number comes before the first element
      }
      if (strcmp(phone, users[length - 1].getPhoneNumber()) > 0) {
         return length; // New phone number comes after the last element
      }

    // Binary search
    while (lowIndex <= highIndex) {
        mid = lowIndex + (highIndex - lowIndex) / 2;

         if (strcmp(phone, users[mid].getPhoneNumber()) >= 0 &&
               (mid == length - 1 || strcmp(phone, users[mid + 1].getPhoneNumber()) < 0)) {
               return mid + 1; // Correct insertion point
         } else if (strcmp(phone, users[mid].getPhoneNumber()) > 0) {
               lowIndex = mid + 1; // Search in the right half
         } else {
               highIndex = mid - 1; // Search in the left half
         }
    }

    return lowIndex; // Fallback (shouldn't reach here due to logic)
}

   void updateUserInfo(){
   int choice;
   do
   {
      cout << "\n========== Update User Information ==========" << endl;
      cout << "1. Update First Name" << endl;
      cout << "2. Update Last Name" << endl;
      cout << "3. Update Phone Number" << endl;
      cout << "4. Update Address" << endl;
      cout << "5. Update Password" << endl;
      cout << "6. Update Total Money (USD)" << endl;
      cout << "7. Update Total Money (KHR)" << endl;
      cout << "8. Exit Update" << endl;
      cout << "Enter your choice: ";
      cin >> choice;

      switch (choice)
      {
      case 1:
      {
         string newFirstName;
         cout << "Enter new first name: ";
         cin >> newFirstName;
         setFirstName(newFirstName);
         cout << "First name updated successfully." << endl;
         break;
      }
      case 2:
      {
         string newLastName;
         cout << "Enter new last name: ";
         cin >> newLastName;
         setLastName(newLastName);
         cout << "Last name updated successfully." << endl;
         break;
      }
      case 3:
      {
         char newPhoneNumber[16];
         cout << "Enter new phone number: ";
         cin >> newPhoneNumber;
         setPhoneNumber(newPhoneNumber);
         cout << "Phone number updated successfully." << endl;
         break;
      }
      case 4:
      {
         string newAddress;
         cout << "Enter new address: ";
         cin.ignore();
         getline(cin, newAddress);
         setAddress(newAddress);
         cout << "Address updated successfully." << endl;
         break;
      }
      case 5:
      {
         char currentPassword[16], newPassword[16], confirmPassword[16];
         cout << "Enter current password: ";
         cin >> currentPassword;

         // Check if current password matches
         if (strcmp(currentPassword, password) != 0)
         {
            cout << "Incorrect current password!" << endl;
            break;
         }

         cout << "Enter new password: ";
         cin >> newPassword;
         cout << "Confirm new password: ";
         cin >> confirmPassword;

         if (strcmp(newPassword, confirmPassword) == 0)
         {
            setPassword(newPassword);
            cout << "Password updated successfully." << endl;
         }
         else
         {
            cout << "Passwords do not match!" << endl;
         }
         break;
      }
      case 6:
      {
         double newUSDAmount;
         cout << "Enter new total USD amount: ";
         cin >> newUSDAmount;
         setTotalMoneyUSD(newUSDAmount);
         cout << "Total USD amount updated successfully." << endl;
         break;
      }
      case 7:
      {
         double newKHRAmount;
         cout << "Enter new total KHR amount: ";
         cin >> newKHRAmount;
         setTotalMoneyKHR(newKHRAmount);
         cout << "Total KHR amount updated successfully." << endl;
         break;
      }
      case 8:
         cout << "Exiting update menu..." << endl;
         break;
      default:
         cout << "Invalid choice. Please try again." << endl;
      }
   } while (choice != 8);
   };
};
//outside class
void readFromCV(const string fileName,ArrayList<User> &users,const string fileNameBin){ 
        ifstream file(fileName);
         if(!file.is_open()){cerr<<"Error"; 
          return ;
         }
         string line;
         int i=0;
    // Read the file line by line
    vector<User> user;
    if(users.getLength()!=0){
      for(int i=0;i<users.getLength();i++){
         user.push_back(users.getValue(i));
      }
    }
    while (getline(file, line)) {
      i++;
      cout<<i<<endl;
      if(i==1){
            getline(file, line);
         }
        stringstream ss(line);
        string fname, lname, address,dob, phoneNum, pw, nationCard, loanKHR, loanUSD, totalKHR, totalUSD;
         
        // Parse the line
        if (getline(ss, fname, ',') &&
            getline(ss, lname, ',') &&
            getline(ss, address, ',') &&
            getline(ss, dob, ',') &&
            getline(ss, phoneNum, ',') &&
            getline(ss, pw, ',') &&
            getline(ss, nationCard, ',') &&
            getline(ss, loanKHR, ',') &&
            getline(ss, loanUSD, ',') &&
            getline(ss, totalKHR, ',') &&
            getline(ss, totalUSD, ',')) {
            
            try {
               //  Convert strings to appropriate data types
                int N_nationCard = stoi(nationCard);
                double N_loanKHR = stod(loanKHR);
                double N_loanUSD = stod(loanUSD);
                double N_totalKHR = stod(totalKHR);
                double N_totalUSD = stod(totalUSD);
                //need add dob
               //  DOB dob(dob);
               const  char*phoneNumber =phoneNum.c_str();
               const char*password=pw.c_str();
               User temp(fname, lname, address,dob, phoneNum.c_str(), pw.c_str(), N_nationCard, N_loanKHR, N_loanUSD, N_totalKHR, N_totalUSD);
               
               if(user.size()>0){
                     try{
                        if(temp.findFreeOrder(user,temp) == user.size()){
                           user.push_back(temp);
                        }else{
                           user.insert(user.begin()+temp.findFreeOrder(user,temp),temp);
                        }
                     }catch(exception &e){
                        cerr<<e.what();
                     }
                  }else{
                     user.push_back(temp);
               }

            } catch (const exception& e) {
                cerr << "Error: Unable to convert one of the numeric values. Skipping this line." << endl;
            }
        } else {
            cerr << "Error: Line format incorrect. Skipping this line." << endl;
         }
      }
      users.setSize(user.size());
      int index =0;
      for(auto i:user){
         users.pushMany(i,index);
         index++;
      }
      writeToBinary(fileNameBin,users);
      file.close();
      cout<<"Success..."<<endl;
   }
   int indexOfUser(char *phone,ArrayList<User> &users){
      int length = users.getLength();
      int lowIndex = 0, mid;
      int highIndex = length - 1;
      if(strcmp(phone, users.getValue(length-1).getPhoneNumber())>0) return length;
      if(strcmp(phone, users.getValue(0).getPhoneNumber())<0) return 0;
      while (lowIndex <= highIndex) {
         mid = lowIndex + (highIndex - lowIndex) / 2;
         if (strcmp(phone,users.getValue(mid).getPhoneNumber())==0  ){
               return mid;
         } else if (strcmp(phone, users.getValue(mid).getPhoneNumber())>0) {
               lowIndex = mid + 1;
         } else {
               highIndex = mid - 1;
         }
         cout<<" Time : "<<endl;
      }
      return -1;
   }
#endif