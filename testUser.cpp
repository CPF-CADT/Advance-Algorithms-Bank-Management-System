//nice
#include<iostream>
#include"utils/User.hpp"
#include"utils/Bank.hpp"

#define USER_FILE "user.bin"
int main(){
   ArrayList<User> user;
   User tempUser;
   int op;
   Bank bank;
   readFromBinary("us.dat",user);
   start:
      cout<<" 1 . Add User"<<endl;
      cout<<" 2 . Transfer"<<endl;
      cout<<"Choose : ";cin>>op;
      switch(op){
         case 1:
            tempUser.input("us.dat");
            tempUser.setTotalMoneyUSD(100);
            tempUser.setTotalMoneyKHR(10000);
            user.push(tempUser);
            writeToBinary("us.dat",user);
            break;
         case 2:  
            char phone[12];
            int source,destination;
            source=1;
            cout<<"Phone Number : ";cin>>phone;
            destination = bank.indexOfUser(phone,user);
            // User& destinationUser = user.getValue(destination);
            user.getValue(1).showBalance();
            user.getValue(destination).showBalance();
            if(destination!=-1){
               user.getValue(source).transferToOtherAccount(user.getValue(destination),4100.00);
            }
            break;
         // case 0:
         //    exit(2);
         // break;
      }
   goto start;
   cin.ignore();
   return 0;
}