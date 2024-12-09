#ifndef ADMIN_HPP
#define ADMIN_HPP
#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
#include"Bank.hpp"
#include"ATM.hpp"
#include"DOB.hpp"
#include"fileHandling.hpp"
#include"User.hpp"

using namespace std;



class Admin {
    private:
    // static int numberUser;
    char userFirstName[45];
        

    public:
    void dataUserHeader(){
        cout << "National-ID   First-Name        Last-Name        Loan-USD        Loan-KHR        Total-Money-KHR   Total-Money-USD   DOB         Phone-Number   Address" << endl;
    }
    void showAllUsers(User user){
        cout << left;
        cout<< setw(15) << user.getNationalIdCard()
        << setw(20) << user.getFirstName()
        << setw(15) << user.getLastName()
        << setw(15) << fixed << setprecision(2) << user.getLoanUSD()
        << setw(15) << fixed << setprecision(2) << user.getLoanKHR()
        << setw(25) << fixed << setprecision(2) << user.getTotalMoneyKHR()
        << setw(10) << fixed << setprecision(2) << user.getTotalMoneyUSD()
        << setw(10) << user.getUserDOB()
        << setw(15) << user.getPhoneNumber()
        << setw(30) << user.getAddress()
        << endl;
        cout << "--------------------------------------------------------------------------------------------------------" << endl;
    }
    void readFromCV(const string & fileName){
        ifstream file(fileName);
        if(!file.is_open()){cerr<<"Error"; 
        return ;
        }else{
            cout<<"yes";
        }
        vector<User> users;
        string line;
        while(getline(file,line)){
            stringstream ss(line);
            string box1,box2;
            if((getline(ss,box1,','))&& getline(ss,box2,',')){
                double Nbox2=stod(box2);
                users.emplace_back(box1,Nbox2);
            }
        }
        file.close();
        for ( auto& User : users) {
            cout << "Field1: " << User.getFirstName()
            << ", Field2: " << User.getLoanUSD()
            << '\n';
        }
    }
};

#endif