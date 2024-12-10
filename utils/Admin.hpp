#ifndef ADMIN_HPP
#define ADMIN_HPP
#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
#include"Bank.hpp"
#include"ATM.hpp"
// #include"fileHandling.hpp"
#include"User.hpp"

using namespace std;
class Admin {
    private:
    // static int numberUser;
    vector<string> userRequest;
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
    void addRequest(User &source,string text){
        string request = " - "+source.getName()+" "+source.getPhoneNumber()+" : \n"+"    "+text+". \n";
        userRequest.push_back(request);
    }
    void showRequest(){
        for (auto request : userRequest) {
            cout << request << endl;
        }     
        cout << "----------------------------------------------------------------------------------------" << endl;
    }
};
#endif