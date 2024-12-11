#include<iostream>
#include"../utils/Admin.hpp"

#define USER_FILE "users.dat"

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
            tempUser.output();
            tempUser.writeToFile(USER_FILE);
            Loan loan;
            loan.applyLoan(tempUser);
            admin.requestLoan(loan);
            user.push(tempUser);
            admin.writeToBinary("admin.dat");
            break;
         }
         case 2:{  
               admin.readBin("admin.dat");
               admin.showLoanRequest();
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