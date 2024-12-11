#include<iostream>
#include"../utils/Admin.hpp"

#define USER_FILE "u.dat"

int main(){
   ArrayList<User> user;
   User tempUser;
   Admin admin;
   int op;
   start:
      cout<<" 1 . Add User"<<endl;
      cout<<" 2 . Show Laon User"<<endl;
      cout<<" 3 . Approve loan for User"<<endl;
      cout<<"Choose : ";cin>>op;
      switch(op){
         case 1:{
            tempUser.input(USER_FILE);
            tempUser.setTotalMoneyUSD(100);
            tempUser.setTotalMoneyKHR(10000);
            if(user.getLength()>0){
               try{
                  if(tempUser.findFreeOrder(user,tempUser) == user.getLength()){
                     user.push(tempUser);
                  }else{
                     user.insertAt(tempUser.findFreeOrder(user,tempUser),tempUser);
                  }
               }catch(exception &e){
                  cerr<<e.what();
               }
            }else{
               user.push(tempUser);
            }
            // user.insertAt(findFreeOrder(user,tempUser),tempUser);
            // writeToBinary(USER_FILE,user);
            break;
         }
         case 2:{  
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