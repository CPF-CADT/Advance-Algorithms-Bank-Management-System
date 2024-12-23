#include<iostream>
#include"../utils/Admin.hpp"

#define USER_FILE "usds2.dat"
using namespace std;
int main(){
   ArrayList<User> user;
   User tempUser;
   Admin admin;
   Bank bank;
   int op;
   Loan loan;
   start:
      cout<<" 1 . Add User"<<endl;
      cout<<" 2 . Show Laon User"<<endl;
      cout<<" 3 . Approve loan for User"<<endl;
      cout<<" 4 . User balance"<<endl;
      cout<<" 5 . Loan Request"<<endl;
      cout<<" 6 . Pay "<<endl;
      cout<<"Choose : ";cin>>op;
      switch(op){
         case 1:{
            tempUser.input(USER_FILE);
            tempUser.setTotalMoneyUSD(100);
            tempUser.setTotalMoneyKHR(10000);
            tempUser.output();
            
            try{
               loan.applyLoan(tempUser,bank);
               admin.getLoan().push(loan);
            }catch(exception &e){
               cerr<<e.what()<<endl;
            }
            if (user.getLength() > 0)
            {
               try
               {
                  if (tempUser.findFreeOrder(user, tempUser) == user.getLength())
                  {
                     user.push(tempUser);
                  }
                  else
                  {
                     user.insertAt(tempUser.findFreeOrder(user, tempUser), tempUser);
                  }
               }
               catch (exception &e)
               {
                  cerr << e.what();
               }
            }
            else
            {
               user.push(tempUser);
            }
            cout<<user.getLength();
            writeToBinary(USER_FILE,user);           
            admin.writeToBinary("ad.bin");
            break;
         }
         case 2:{  
               admin.readBin("ad.bin");
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
                        user.getValue(index).addLoanMoneyKHR(admin.getLoan().getValue(i).getAmountWithInterest());
                        
                     }else {
                        user.getValue(index).addMoneyUSD(admin.getLoan().getValue(i).getAmountLoan().getAmountUSD());
                        user.getValue(index).addLoanMoneyUSD(admin.getLoan().getValue(i).getAmountWithInterest());

                     }
                     cout<<"yes and done!!"<<endl;
                     admin.showUserLoan();
                     admin.getListLoanUser().push(admin.getLoan().getValue(i));
                     admin.getLoan().removeAt(i);
                     admin.writeToBinary("ad.bin");
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
         case 4:
            readFromBinary(USER_FILE,user);
            cout<<user.getLength();
            for( int i=0;i<user.getLength();i++){
               user.getValue(i).displayInfo();
            }
         break;
         case 5:{
            admin.readBin("ad.bin");
            admin.showUserLoan();
            admin.showRequest();
            break;
            }
         case 6:{
            admin.readBin("ad.bin");
            char phone[12];
            int op;
            cout << "Phone number : ";
            cin >> phone;
            for(int i=0;i<admin.getListLoanUser().getLength();i++){
               if(strcmp(phone,admin.getListLoanUser().getValue(i).getPhoneNumber())==0){
                  user.getValue(indexOfUser(phone,user));
                  cout<<"Amount : "<<admin.getListLoanUser().getValue(i).payBack(user.getValue(indexOfUser(phone,user)))<<endl;
                  admin.getListLoanUser().getValue(i).listPayBack();
               }
            }
            break;
            }

      }
   goto start;
   cin.ignore();
   return 0;
}