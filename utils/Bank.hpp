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
      intrestKHR[0]  = 0.0;
      interestKHR[1] = 0.0;
      interestKHR[2] = 0.0;
      interestKHR[3] = 0.0;

      interestUSD[0] = 0.0;
      interestUSD[1] = 0.0;
      interestUSD[2] = 0.0;
      interestUSD[3] = 0.0;
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
   
};
#endif