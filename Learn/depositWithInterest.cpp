#include<iostream>
#include"../utils/Admin.hpp"
#include"../utils/DepositWithInterest.hpp"
#define USER_FILE "users.dat"
int main(){
   Bank bank;
   DepositInterest depo;
   depo.depositWithInterest(bank,100000000,10000);
   Date cur;
   cout<<depo.payBack(cur);
   cur.nextManyMonth(1);
   depo.infor();
   // cur.nextManyMonth(2);
   // cout<<depo.payBack(cur);
   // depo.infor(); 
   // cur.nextManyMonth(3);
   // cout<<depo.payBack(cur);
   // depo.infor(); 
   // cur.nextManyMonth(4);
   // cout<<depo.payBack(cur);
   // depo.infor(); 
}