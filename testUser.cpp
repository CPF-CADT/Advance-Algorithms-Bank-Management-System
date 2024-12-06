//nice
#include<iostream>
#include"utils/User.hpp"

#define USER_FILE "user.bin"
int main(){
   ArrayList<User> user;
   User tempUser;
   tempUser.input("tst.dat");
   tempUser.setTotalMoneyKHR(100000);
   tempUser.setTotalMoneyUSD(1000);
   tempUser.showBalance();
   tempUser.transferOwnAccount(4100);
   tempUser.showBalance();
   cin.ignore();
   return 0;
}