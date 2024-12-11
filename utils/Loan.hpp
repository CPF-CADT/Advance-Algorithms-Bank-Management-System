#include"Date.hpp"
#include"User.hpp"
class Loan{
   private:
      double khr;
      double usd;
      string reason;
      Date returnMoney;
      Date takeMoney;
      char phoneNumber[12];
      string name;
   public:
      Loan(){
         khr = 0;
         usd = 0;
         reason = "NULL";
         strcpy(phoneNumber,"NULL");
         name = "NULL";
      }
      void applyLoan(User & users){
         
      }

      void setKHR(double khrValue) {
         khr = khrValue;
      }


    void setUSD(double usdValue) {
        usd = usdValue;
    }

    void setReason(string& reasonValue) {
        reason = reasonValue;
    }

    void setReturnMoney(string& returnMoneyValue) {
        returnMoney = returnMoneyValue;
    }

    void setTakeMoney(string& takeMoneyValue) {
        takeMoney = takeMoneyValue;
    }

    void setPhoneNumber(char* phone) {
        strncpy(phoneNumber, phone, sizeof(phoneNumber) - 1);
        phoneNumber[sizeof(phoneNumber) - 1] = '\0';
    }

    void setName(string& nameValue) {
        name = nameValue;
    }
    double getKHR() {
        return khr;
    }

    double getUSD() {
        return usd;
    }

    string getReason() {
        return reason;
    }

    string getReturnMoney() {
        return returnMoney;
    }

    string getTakeMoney() {
        return takeMoney;
    }

    string getPhoneNumber() {
        return string(phoneNumber);
    }

    string getName() {
        return name;
    }
      
}