#ifndef DEPOSIT_INTEREST
#define DEPOSIT_INTEREST
#include"Bank.hpp"
#include"QRCode.hpp"
#include"Date.hpp"
#include <iomanip> 
#define DATA_USER_DEPOSIT "../Data/dataUserDepositt.dat"
class DepositInterest{
   private:
      double amountKHR;
      double amountUSD;
      double amountWithInterestKHR;
      double amountWithInterestUSD;
      double interestMoney;
      int numberOfPayBack;
      int countPayback;
      Date depositDate;
      Date endDateOfDeposit;
      Date payDaily[24];
   public:
      DepositInterest(){
         amountKHR = 0.00;
         amountUSD = 0.00;
         amountWithInterestKHR = 0.00;
         amountWithInterestUSD = 0.00;
         numberOfPayBack = 0;
         interestMoney = 0.0;
         countPayback = 0;
      }
      int choosePayback(int month){
         int op;
         cout << "Select the type of interest payout for your deposit:" << endl;
         cout << "1. Receive interest monthly"<< endl; //need display money per month
         cout << "2. Receive interest at the end of the term"<< endl;
         cout<<"Choose : ";cin>>op;
         switch(op){
            case 1:
               return month;
               break;
            case 2:
               return 1;
               break;
         }
         return -1;
      }
      void receipt(){
         char curency;
         cout << "\n=====================================" << endl;
         cout << "          DEPOSIT SUMMARY            " << endl;
         cout << "=====================================" << endl;
         if(amountKHR>0){
            curency = 'R';
            cout << "Amount Deposited:           " << amountKHR << " R" << endl;
            cout << "Total Amount with Interest: " << fixed <<setprecision(2)<< amountWithInterestKHR << " R" << endl;
         }else{
            curency = '$';
            cout << "Amount Deposited:           " << amountUSD << " $" << endl;
            cout << "Total Amount with Interest: "  << fixed <<setprecision(2)<< amountWithInterestUSD << " &" << endl;
         }
            cout<<"Deposit Date : "<<depositDate.getDate()<<endl;
            cout<<"End of Term  : "<<endDateOfDeposit.getDate()<<endl;
         if (numberOfPayBack == 1) {
            cout << "payout Type: Interest will be paid in one installment at the end of the term." << endl;
         } else if (numberOfPayBack > 1) {
            cout << "payout Type: Interest will be paid "  << fixed <<setprecision(2)<< (interestMoney/numberOfPayBack)<<curency << " monthly" << endl;
            for(int i = 0 ;i<numberOfPayBack;i++){
               cout<<i+1<<" . "<<payDaily[i].getDate()<<endl;
            }
         } else {
            cout << "payout Type: Invalid selection. Please check again." << endl;
         }
         cout << "=====================================" << endl;
      }
      void calculateAmount(int typeDuration,float interestType){
         interestType/=100;
         if(amountKHR>0){
            this->amountWithInterestKHR= amountKHR+ (amountKHR * interestType);
            this->interestMoney = amountKHR * interestType;
         }else{
            this->amountWithInterestUSD = amountUSD+ (amountUSD* interestType);
            this->interestMoney = amountUSD * interestType;
         }
      }
      void depositWithInterest(Bank &bank,double totalUSD,double totalKHR){
         QRCode depositMoney;
         float *interest;
         int op;
         depositMoney.cratePaymentCode();
         if(depositMoney.getAmountKHR()>0){
            interest = bank.getInterestKHR();
            amountKHR = depositMoney.getAmountKHR();
            if(amountKHR<400000){
               throw runtime_error ("KHR Must grater that 400000 R");
            }
         }else{
            interest = bank.getInterestUSD();
            amountUSD = depositMoney.getAmountUSD();
            if(amountUSD<100){
               throw runtime_error("USD Must grater that 100$");
            }
         }
         if(totalUSD<depositMoney.getAmountUSD() || totalKHR < depositMoney.getAmountKHR()){
            throw runtime_error("Not Enough Money");
         }
         depositDate.setCurrentDate();
         cout<<"Duration Type "<<endl;
         cout<<"1 . 3  Month (interest "<<interest[0]<<"% )."<<endl;
         cout<<"2 . 6  Month (interest "<<interest[1]<<"% )."<<endl;
         cout<<"3 . 12 Month (interest "<<interest[2]<<"% )."<<endl;
         cout<<"4 . 24 Month (interest "<<interest[3]<<"% )."<<endl;
         cout<<"0 . Exit"<<endl;
         cout<<"Choose : ";cin>>op;
         switch(op){
            case 1:
               numberOfPayBack = choosePayback(3);
               calculateAmount(3,interest[0]);
               endDateOfDeposit.nextManyMonth(3);
               break;
            case 2:
               numberOfPayBack = choosePayback(6);
               calculateAmount(6,interest[1]);
               endDateOfDeposit.nextManyMonth(6);
               break;
            case 3:
               numberOfPayBack = choosePayback(12);
               calculateAmount(12,interest[2]);
               endDateOfDeposit.nextManyMonth(12);
               break;
            case 4:
               numberOfPayBack = choosePayback(24);
               calculateAmount(24,interest[3]);
               endDateOfDeposit.nextManyMonth(24);
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
         receipt();
      }
      void infor(){
         if(amountKHR>0){
            cout<<" - KHR: " << amountKHR <<"R"<< endl;
         }else{
            cout<<" - USD: " << amountUSD<<"$"<< endl;
         }
         cout<<" > Deposit Date : "<<depositDate.getDate()<<endl;
         if(numberOfPayBack>1){
            cout<<"> Payout Date  : "<<endl;
            for(int i = countPayback ;i<numberOfPayBack;i++){
               cout<<i+1<<" . "<<payDaily[i].getDate()<<endl;
            }
         }else{
            cout<<" > Payout Date  : "<<endDateOfDeposit.getDate()<<endl;
         }
         cout<<"--------------------------------------"<<endl;
      }
      double payBack(Date current){
         if(numberOfPayBack == 1 && numberOfPayBack!=countPayback){
            countPayback+=1;
            return interestMoney;
         }
         if(numberOfPayBack>1 && numberOfPayBack!=countPayback){
            if(current.getDate() == payDaily[countPayback].getDate()){
               countPayback+=1;
               return(interestMoney/numberOfPayBack);
            }
         }
         return 0.00;
      }
      void setAmountKHR(double amount) {
         amountKHR = amount;
      }
      double getAmountKHR() const {
         return amountKHR;
      }
      void setAmountUSD(double amount) {
         amountUSD = amount;
      }
      double getAmountUSD() const {
         return amountUSD;
      }
      void setAmountWithInterestKHR(double amount) {
         amountWithInterestKHR = amount;
      }
      double getAmountWithInterestKHR() const {
         return amountWithInterestKHR;
      }
      void setAmountWithInterestUSD(double amount) {
         amountWithInterestUSD = amount;
      }
      double getAmountWithInterestUSD() const {
         return amountWithInterestUSD;
      }
      void setInterestMoney(double interest) {
         interestMoney = interest;
      }
      double getInterestMoney() const {
         return interestMoney;
      }
      void setNumberOfPayBack(int number) {
         numberOfPayBack = number;
      }
      int getNumberOfPayBack() const {
         return numberOfPayBack;
      }

};
#endif