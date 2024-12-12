#ifndef ATM.HPP
#define ATM.HPP
#include<vector>
#include<iostream>
#include<string>
#include "User.hpp"
using namespace std;

    class ATM{
        private:
        vector<User> users;
    }
        public:
            AMT(){
                users.pushback(User("085825783"), 1000);
            }
            User* searchUser(const string& phoneNumber){
                for(auto& user : users ){
                    if ( user.getPhoneNumber() == phoneNumber){
                        return &user;
                    }
                }
                return nullptr;
            }
            void withdraw(User& user){
                cout<<"Your current balance : $" << User.getbalance<<
            }
