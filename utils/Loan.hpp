#ifndef LOAN_HPP
#define LOAN_HPP
#include"Date.hpp"
#include"User.hpp"
#include"QRCode.hpp"
class Loan{
   private:
      QRCode amountLoan;
      string name;
      string reason;
      Date takeMoney;
      Date returnMoney;
      char phoneNumber[12];

   public:
        Loan(){
            reason = "NULL";
            strcpy(phoneNumber,"NULL");
            name = "NULL";
        }
        void applyLoan(User & users){
            amountLoan.cratePaymentCode();
            cin.ignore();
            cout<<"Reason : ";getline(cin,reason);
            cout<<"Return Date : \n";
            takeMoney.setCurrentDate();
            returnMoney.inputDate();
            strcpy(phoneNumber,users.getPhoneNumber());
            name = users.getName();
        }
        void writeToBin(ofstream &writeFile){
            writeFile.write((char *)(&amountLoan), sizeof(QRCode));    
            writeString(writeFile,name);
            writeString(writeFile,reason);
            writeFile.write((char *)(&takeMoney), sizeof(Date));    
            writeFile.write((char *)(&returnMoney), sizeof(Date)); 
            writeFile.write((char *)(&phoneNumber),sizeof(phoneNumber));  
        }
        void readBin(ifstream &readFile){
            readFile.read((char *)(&amountLoan), sizeof(QRCode));    
            name = readString(readFile);
            reason = readString(readFile);
            readFile.read((char *)(&takeMoney), sizeof(Date));    
            readFile.read((char *)(&returnMoney), sizeof(Date)); 
            readFile.read((char *)(&phoneNumber),sizeof(phoneNumber));  
        }
        void setReason(string& reasonValue) {
            reason = reasonValue;
        }
        void showLoanDetail(){
            cout << left << setw(20) << "Name" << setw(15) << "Phone" << endl;
            cout << "------------------------------------------------------------" << endl;
            cout << left << setw(20) << name << setw(15) << phoneNumber << endl;
            cout << endl;
            cout << "Loan Amount        : " <<amountLoan.getLoanData() << endl;
            cout << "Reason             : " << reason << endl;
            cout << "Take Money Date    : " << takeMoney.getDate() << endl;
            cout << "Return Money Date  : " << returnMoney.getDate() << endl;
        }
        void setPhoneNumber(char* phone) {
            strncpy(phoneNumber, phone, sizeof(phoneNumber) - 1);
            phoneNumber[sizeof(phoneNumber) - 1] = '\0';
        }
        void setName(string& nameValue) {
            name = nameValue;
        }
        string getReason() {
            return reason;
        }
        string getPhoneNumber() {
            return string(phoneNumber);
        }
        string getName() {
            return name;
        }
        QRCode & getAmountLoan(){
            return amountLoan;
        }
        Date getRetunDate(){
            return returnMoney;
        }
        Date getTakeDate(){
            return takeMoney;
        }
      
};
#endif