#include<iostream>
#include"../utils/arrayList.hpp"
#include"../utils/fileHandling.hpp"
#include"../utils/Admin.hpp"
#define USER_FILE "user.dat"
int main(){
   ArrayList<User> users;
   Admin admin;
   // readFromBinary(USER_FILE,users);
   // string request;
   // cout<<"Re : ";getline(cin,request);
   // admin.addRequest(users.getValue(0),request);
   // admin.showRequest();
   // cout<<"Re : ";getline(cin,request);
   // admin.addRequest(users.getValue(0),request);
   admin.readBin("assa.dat");
   admin.showRequest();
   // admin.writeToBinary("assa.dat");
   return 0;
}