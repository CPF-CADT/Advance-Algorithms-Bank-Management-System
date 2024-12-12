#include<iostream>
#include"../utils/Admin.hpp"
#include"../utils/DepositWithInterest.hpp"
#define USER_FILE "users.dat"
int main(){
   Bank bank;
   DepositInterest depo;
   depo.depositWithInterest(bank);
}