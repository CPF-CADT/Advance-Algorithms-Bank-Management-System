#ifndef DEPOSIT_INTEREST
#define DEPOSIT_INTEREST
#include"Bank.hpp"
#include"QRCode.hpp"
#include <iomanip> 
class DepositInterest{
   private:
      double amountKHR;
      double amountUSD;
      double amountWithInterestKHR;
      double amountWithInterestUSD;
      double interestMoney;
      int numberOfPayBack;
   public:
      DepositInterest(){
         amountKHR = 0.00;
         amountUSD = 0.00;
         amountWithInterestKHR = 0.00;
         amountWithInterestUSD = 0.00;
         numberOfPayBack = 0;
         interestMoney = 0.0;
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

         if (numberOfPayBack == 1) {
            cout << "payout Type: Interest will be paid in one installment at the end of the term." << endl;
         } else if (numberOfPayBack > 1) {
            cout << "payout Type: Interest will be paid "  << fixed <<setprecision(2)<< (interestMoney/numberOfPayBack)<<curency << " monthly" << endl;
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
      void depositWithInterest(Bank &bank){
         QRCode depositMoney;
         float *interest;
         int op;
         depositMoney.cratePaymentCode();
         if(depositMoney.getAmountKHR()>0){
            interest = bank.getInterestKHR();
            amountKHR = depositMoney.getAmountKHR();
         }else{
            interest = bank.getInterestUSD();
            amountUSD = depositMoney.getAmountUSD();
         }
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
               break;
            case 2:
               numberOfPayBack = choosePayback(6);
               calculateAmount(6,interest[1]);
               break;
            case 3:
               numberOfPayBack = choosePayback(12);
               calculateAmount(12,interest[2]);
               break;
            case 4:
               numberOfPayBack = choosePayback(24);
               calculateAmount(24,interest[3]);
               break;
            case 0:
               return;
               break;
         }
         receipt();
      }
};
#endif