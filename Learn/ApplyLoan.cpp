#include<iostream>
#include"../utils/Admin.hpp"

#define USER_FILE "usds2.dat"
using namespace std;
int main(){
   ArrayList<User> user;
   User tempUser;
   Admin admin;
   int op;
   Loan loan;
   try
   {
      /* code */
   readFromBinary(USER_FILE,user);
   admin.readBin("ad12.dat");
   }
   catch(const std::exception& e)
   {
      std::cerr << e.what() << '\n';
   }
   
  
   start:
      cout<<" 1 . Add User"<<endl;
      cout<<" 2 . Show Laon User"<<endl;
      cout<<" 3 . Approve loan for User"<<endl;
      cout<<" 4 . User balance"<<endl;
      cout<<" 7 . Pay back"<<endl;

      cout<<"Choose : ";cin>>op;
      switch(op){
         case 1:{
            tempUser.input(USER_FILE);
            tempUser.setTotalMoneyUSD(100);
            tempUser.setTotalMoneyKHR(10000);
            tempUser.output();

            
            loan.applyLoan(tempUser);
            admin.getLoan().push(loan);
            user.push(tempUser);
            tempUser.writeToFile(USER_FILE);
            admin.writeToBinary("ad12.dat");
            break;
         }
         case 2:{  
               admin.readBin("ad12.dat");
               admin.showLoanRequest();
            break;
         }
         case 3:
            int code;
            int indexOfloan;
            char choice;
            again:
            cout<<"Input the code to aprove :"; cin>>code;
            for(int i=0;i< admin.getLoan().getLength();i++){
                  if(code == admin.getLoan().getValue(i).getAmountLoan().getCode() ){
                     admin.getLoan().getValue(i).showLoanDetail();
                     cout<<"Is it a right one? (Y/N)";cin>>choice;
                     switch (choice)
                     {
                     case 'Y':{
                     // char* phone=l.getPhoneNumber();
                     try
                     {
                        /* code */
                     
                     int index = indexOfUser(admin.getLoan().getValue(i).getPhoneNumber(),user);
                     cout<<index<<"hello"<<endl<<endl;
                     if(admin.getLoan().getValue(i).getAmountLoan().getAmountKHR()>0){
                        user.getValue(index).addMoneyKHR(admin.getLoan().getValue(i).getAmountLoan().getAmountKHR());
                        user.getValue(index).addLoanMoneyKHR(admin.getLoan().getValue(i).getAmountLoan().getAmountKHR());
                        
                     }else {
                        user.getValue(index).addMoneyUSD(admin.getLoan().getValue(i).getAmountLoan().getAmountUSD());
                        user.getValue(index).addLoanMoneyUSD(admin.getLoan().getValue(i).getAmountLoan().getAmountUSD());

                     }
                     cout<<"yes and done!!"<<endl;
                     admin.showUserLoan();
                     admin.getListLoanUser().push(admin.getLoan().getValue(i));
                     admin.getLoan().removeAt(i);
                     admin.writeToBinary("ad12.dat");
                     writeToBinary(USER_FILE,user);           
                     }
                     catch(const std::exception& e)
                     {
                        std::cerr << e.what() << '\n';
                     }
                  
                        break;
                        }
                        case 'N':{
                           cout<<"Okey"<<endl;
                           goto start;
                        }
                        
                     
                     default:
                        break;
                     }
               break; 
            }
        }
         break;
         case 7:
         //payback
         

         case 4:
            for( int i=0;i<user.getLength();i++){
               user.getValue(i).displayInfo();
            }
         break;
         case 5:{
            admin.readBin("ad12.dat");
            admin.showUserLoan();
            admin.showRequest();
            break;
            }

      }
   goto start;
   cin.ignore();
   return 0;
}