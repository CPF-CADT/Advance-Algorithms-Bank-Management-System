#include<iostream>
#include"utils/User.hpp"
#include <cstdlib>

#define USER_FILE "users.bin"
int User::numberOfUser = 0;
int main(){
   ArrayList<User> user;
   const char* command1 = "git pull";
   const char* command2 = "git add .";
   const char* command3 = "git commit -m \"update\" ";
   const char* command4 = "git push";
   User tempUser;
   //if want to add pls run code from 14 to 21
   tempUser.input(USER_FILE);
   user.push(tempUser);
   writeToBinary(USER_FILE,user);
   system(command1);
   system(command2);
   system(command3);
   system(command4);

   // for show run code below
   // system(command1);
   // readFromBinary(USER_FILE,user);
   // for(int i=0;i<user.getLength();i++){
   //    tempUser=user.getValue(i);
   //    tempUser.output();
   // }

   return 0;
}