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
      // for(int i=0;i<users.getLength();i++){
      //    if(strcmp(phone,users.getValue(i).getPhoneNumber()) == 0 ){
      //       return i;
      //    }
      // }
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
      }
      return -1;
   }
   
};

#endif