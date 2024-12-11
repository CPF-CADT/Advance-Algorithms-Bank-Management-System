#include<iostream>
#include"../utils/User.hpp"

#define USER_FILE "user.dat"

int main(){
   ArrayList<User> user;
   User tempUser;
   int op;
   start:
      cout<<" 1 . Add User"<<endl;
      cout<<" 1 . Apply User"<<endl;
      cout<<" 1 . Approve User"<<endl;
      cout<<"Choose : ";cin>>op;
      switch(op){
         case 1:{
            tempUser.input(USER_FILE);
            tempUser.setTotalMoneyUSD(100);
            tempUser.setTotalMoneyKHR(10000);
            tempUser.output();
            tempUser.writeToFile(USER_FILE);
            user.push(tempUser);
            break;
         }
         case 2:{  
            readFromBinary(USER_FILE,user);
            for(int i=0;i<user.getLength();i++){
               user.getValue(i).output();
            }
            break;
         }
         // case 3:
         // ofstream writeFile(USER_FILE,ios::binary);
         //    for(int i=0;i<user.getLength();i++){
         //       user.getValue(i).writeToFile(writeFile);
         //    }
         // break;
      }
   goto start;
   cin.ignore();
   return 0;
}