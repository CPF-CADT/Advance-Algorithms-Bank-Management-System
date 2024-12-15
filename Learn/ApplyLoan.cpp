#include<iostream>
#include"../utils/Admin.hpp"

#define USER_FILE "us.dat"
using namespace std;
int main(){
   ArrayList<User> user;
   User tempUser;
   Admin admin;
   int op;
   Loan loan;
   readFromBinary(USER_FILE,user);
   admin.readBin("ad.dat");
   start:
      cout<<" 1 . Add User"<<endl;
      cout<<" 2 . Show Laon User"<<endl;
      cout<<" 3 . Approve loan for User"<<endl;
      cout<<" 4 . User balance"<<endl;

      cout<<"Choose : ";cin>>op;
      switch(op){
         case 1:{
            tempUser.input(USER_FILE);
            tempUser.setTotalMoneyUSD(100);
            tempUser.setTotalMoneyKHR(10000);
            tempUser.output();
            tempUser.writeToFile(USER_FILE);
            
            loan.applyLoan(tempUser);
            admin.requestLoan(loan);
            user.push(tempUser);
            admin.writeToBinary("ad.dat");
            break;
         }
         case 2:{  
               admin.readBin("ad.dat");
               admin.showLoanRequest();
            break;
         }
         case 3:
            int code;
            char choice;
            again:
            cout<<"Input the code to aprove :"; cin>>code;
            for(auto l:admin.getLoan()){
                  if(code == l.getAmountLoan().getCode() ){
                     l.showLoanDetail();
                     cout<<"Is it a right one? (Y/N)";cin>>choice;
                     switch (choice)
                     {
                     case 'Y':{
                     // char* phone=l.getPhoneNumber();
                     try
                     {
                        /* code */
                           
                     int index = indexOfUser(l.getPhoneNumber(),user);
                     cout<<index<<"hello";
                     if(l.getAmountLoan().getAmountKHR()>0){
                        user.getValue(index).addMoneyKHR(l.getAmountLoan().getAmountKHR());
                        user.getValue(index).addLoanMoneyKHR(l.getAmountLoan().getAmountKHR());
                     }else {
                        user.getValue(index).addMoneyUSD(l.getAmountLoan().getAmountUSD());
                        user.getValue(index).addLoanMoneyUSD(l.getAmountLoan().getAmountUSD());

                     }
                     cout<<"yes";
                                 writeToBinary(USER_FILE,user);

                     
                     }
                     catch(const std::exception& e)
                     {
                        std::cerr << e.what() << '\n';
                     }
                  
                        break;}
                     
                     default:
                        break;
                     }
            }
        }
         break;
         case 4:
            for( int i=0;i<user.getLength();i++){
               user.getValue(i).displayInfo();
            }
         break;

      }
   goto start;
   cin.ignore();
   return 0;
}