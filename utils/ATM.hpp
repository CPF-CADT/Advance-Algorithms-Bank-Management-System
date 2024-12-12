#ifndef ATM.HPP
#define ATM.HPP
#include<vector>
#include<iostream>
#include<string>

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

