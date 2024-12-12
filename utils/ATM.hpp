#ifndef ATM.HPP
#define ATM.HPP

#include "User.hpp"
#include <string>
#include<iostream>

using namespace std;

class ATM {
    private:
        int balance;
    public:
        ATM(int bal){
            balance = bal;
        }
        int getBalance(){
            return balance;
        }
        int withdraw(int amount){
            if(amount > balance ){
                return false;
            } else {
                balance = balance - amount;
                    return true;
            }
        }
        int deposite(int amount){
            balance = balance + amount;
        }
};
#endif