#ifndef LOAN_HPP
#define LOAN_HPP
#include"Date.hpp"
#include"User.hpp"
#include"QRCode.hpp"
#include"Bank.hpp"
class Loan{
   private:
        QRCode amountLoan;
        string name;
        string reason;
        Date takeMoney;
        Date returnMoney;
        char phoneNumber[12];
        int numberOfPayBack;
        int countPayback;
        Date payDaily[24];
        double amountWithInterestKHR;
        double amountWithInterestUSD;
   public:
        Loan(){
            reason = "NULL";
            strcpy(phoneNumber,"NULL");
            name = "NULL";
            numberOfPayBack = 0;
            countPayback = 0;
            amountWithInterestKHR =0;
            amountWithInterestUSD =0;
        }
        void calculateAmount(int typeDuration,float interestType){
            interestType/=100;
            if(amountLoan.getAmountKHR()>0){
                this->amountWithInterestKHR= amountLoan.getAmountKHR()+ (amountLoan.getAmountKHR() * interestType);
            }else{
                this->amountWithInterestUSD = amountLoan.getAmountUSD()+ (amountLoan.getAmountUSD()* interestType);
            }
        }
        void applyLoan(User & users, Bank bank){
            float *interest;
            int op;
            amountLoan.cratePaymentCode();
            if(amountLoan.getAmountKHR()>0){
                interest = bank.getInterestKHR();
                if(amountLoan.getAmountKHR()<400000 && amountLoan.getAmountKHR()!=0){
                        throw runtime_error ("KHR Must grater that 400000 R");
                    }
            }else{
                interest = bank.getInterestUSD();
                if(amountLoan.getAmountUSD()<100){
                    throw runtime_error("USD Must grater that 100$");
                }
            }
            cin.ignore();
            cout<<"Reason : ";getline(cin,reason);
            takeMoney.setCurrentDate();
            strcpy(phoneNumber,users.getPhoneNumber());
            name = users.getName();
            cout<<"Duration Type "<<endl;
            cout<<"1 . 3  Month (interest "<<interest[0]<<"% )."<<endl;
            cout<<"2 . 6  Month (interest "<<interest[1]<<"% )."<<endl;
            cout<<"3 . 12 Month (interest "<<interest[2]<<"% )."<<endl;
            cout<<"4 . 24 Month (interest "<<interest[3]<<"% )."<<endl;
            cout<<"0 . Exit"<<endl;
            cout<<"Choose : ";cin>>op;
            switch(op){
                case 1:{
                numberOfPayBack = 3;
                calculateAmount(3,interest[0]);
                returnMoney.nextManyMonth(3);}
                break;
                case 2:{
                numberOfPayBack = 6;
                calculateAmount(6,interest[1]);
                returnMoney.nextManyMonth(6);}
                break;
                case 3:{
                numberOfPayBack = 12;
                calculateAmount(12,interest[2]);
                returnMoney.nextManyMonth(12);}
                break;
                case 4:{
                numberOfPayBack = 24;
                calculateAmount(24,interest[3]);
                returnMoney.nextManyMonth(24);}
                break;
                case 0:
                return;
                break;
            }
            Date payDate;
            for(int i=1;i<=numberOfPayBack;i++){
                payDate.nextManyMonth(i);
                payDaily[i-1]=payDate;
            }
            showLoanDetail();
        }
        void writeToBin(ofstream &writeFile){
            writeFile.write((char *)(&amountLoan), sizeof(QRCode));    
            writeString(writeFile,name);
            writeString(writeFile,reason);
            writeFile.write((char *)(&takeMoney), sizeof(Date));    
            writeFile.write((char *)(&returnMoney), sizeof(Date)); 
            writeFile.write((char *)(&numberOfPayBack),sizeof(numberOfPayBack));  
            writeFile.write((char *)(&countPayback),sizeof(countPayback));  
            for(int j=0;j<numberOfPayBack;j++){
                writeFile.write((char *)(&payDaily[j]), sizeof(Date)); 
            }
            writeFile.write((char *)(&phoneNumber),sizeof(phoneNumber));  
            writeFile.write((char *)(&amountWithInterestKHR),sizeof(amountWithInterestKHR));  
            writeFile.write((char *)(&amountWithInterestUSD),sizeof(amountWithInterestUSD));  
        }
        void readBin(ifstream &readFile){
            readFile.read((char *)(&amountLoan), sizeof(QRCode));    
            name = readString(readFile);
            reason = readString(readFile);
            readFile.read((char *)(&takeMoney), sizeof(Date));    
            readFile.read((char *)(&returnMoney), sizeof(Date)); 
            readFile.read((char *)(&numberOfPayBack),sizeof(numberOfPayBack));  
            readFile.read((char *)(&countPayback),sizeof(countPayback));  
            for(int j=0;j<numberOfPayBack;j++){
                readFile.read((char *)(&payDaily[j]), sizeof(Date));            
            }
            readFile.read((char *)(&phoneNumber),sizeof(phoneNumber));  
            readFile.read((char *)(&amountWithInterestKHR),sizeof(amountWithInterestKHR));  
            readFile.read((char *)(&amountWithInterestUSD),sizeof(amountWithInterestUSD));  
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
            cout << "------------------------------------------------------------" << endl;
            listPayBack();
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
        char* getPhoneNumber() {
            return phoneNumber;
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
        double getAmountWithInterest(){
            if(amountWithInterestKHR>0){
                return amountWithInterestKHR;
            }else{
                return amountWithInterestUSD;
            }
        }
        double payBack(User &user){
            if(numberOfPayBack>0 && numberOfPayBack!=countPayback){
                countPayback+=1;
                if(countPayback==numberOfPayBack){
                    user.setLoanKHR(0);
                    user.setLoanUSD(0);
                    cout<<"Finished Loan..."<<endl;
                    return 0.0;
                }
                if(amountLoan.getAmountKHR()>0){
                    user.setLoanKHR(user.getLoanKHR()-(amountWithInterestKHR/numberOfPayBack));
                    return (amountWithInterestKHR/numberOfPayBack);
                }
                user.setLoanUSD(user.getLoanUSD()-(amountWithInterestUSD/numberOfPayBack));
                return amountWithInterestUSD/numberOfPayBack;
            }
            return 0.00;
        }
        void listPayBack(){
            cout << "Interest next paid " << endl;
            for(int i = countPayback ;i<numberOfPayBack;i++){
               cout<<i+1<<" . "<<payDaily[i].getDate()<<endl;
            }
        }
        //  double getLoanData() const {
        //     return loanAmount;
        // }
        
      
};
#endif