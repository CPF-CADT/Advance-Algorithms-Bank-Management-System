#ifndef BANK_HPP
#define BANK_HPP
#include "./User.hpp"
#include "./arrayList.hpp"
class Bank{
private:
   int totalUser;
   float exchangeRateUSDtoKHR;
   double totalMoneyKHR;
   double totalMoneyUSD;
   //string report;
   //string History-Transaction;
public:
   Bank(){
      totalUser = 0;
      exchangeRateUSDtoKHR = 0.0;
      totalMoneyKHR = 0.0;
      totalMoneyUSD = 0.0;
   }
   void setExchnageRate(float rate){
      this->exchangeRateUSDtoKHR = rate;
   }
   float getExchnageRate(){
      return exchangeRateUSDtoKHR;
   }
   int indexOfUser(char *phone,ArrayList<User> &users){
      //need to apply binary search
      for(int i=0;i<users.getLength();i++){
         if(strcmp(phone,users.getValue(i).getPhoneNumber()) == 0 ){
            return i;
         }
      }
      return -1;
   }
   
};

#endif