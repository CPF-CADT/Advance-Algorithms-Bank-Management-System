#ifndef BANK_HPP
#define BANK_HPP
#include "./arrayList.hpp"
#include<vector>
class Bank{
private:
   long totalUser;
   float exchangeRateUSDtoKHR;
   float intrestKHR[4];
   float intrestUSD[4];
   double totalMoneyKHR;
   double totalMoneyUSD;
   vector<string> report;
   vector<string> HistoryTransaction;
public:
   Bank(){
      totalUser = 0;
      exchangeRateUSDtoKHR = 0.0;
      intrestKHR[0] = 3.20;
      intrestKHR[1] = 4.20;
      intrestKHR[2] = 4.40;
      intrestKHR[3] = 4.95;

      intrestUSD[0] = 1.80;
      intrestUSD[1] = 2.80;
      intrestUSD[2] = 3.15;
      intrestUSD[3] = 3.80;
      totalMoneyKHR= 0.0;
      totalMoneyUSD= 0.0;
   }
   void setExchnageRate(float rate){
      this->exchangeRateUSDtoKHR = rate;
   }
   float getExchnageRate(){
      return exchangeRateUSDtoKHR;
   }
   void addNewUser(){
      totalUser+=1;
   }
   void setInterestKHR(int index,float interest){
      intrestKHR[index] = interest;
   }
   void setInterestUSD(int index,float interest){
      intrestUSD[index] = interest;
   }
   float *getInterestKHR(){
      return intrestKHR;
   }
   float *getInterestUSD(){
      return intrestUSD;
   }
   long getTotalUsers(){
      return totalUser;
   }
   void setReport(string text){
      report.push_back(text);
   }

   
};
#endif