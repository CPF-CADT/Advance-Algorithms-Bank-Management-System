#ifndef ADMIN_HPP
#define ADMIN_HPP
#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
#include"Bank.hpp"
#include"ATM.hpp"
#include"fileHandling.hpp"
#include"User.hpp"
#include"Loan.hpp"
using namespace std;
class Admin {
    private:
    // static int numberUser;
    // vector<string> userRequest;
    LinkList<Loan> loanRequest;
    Bank* bank;
    public:
    // Admin()
    // }
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
    void requestLoan( Loan loanReq){
        loanRequest.push(loanReq);
    }
    void showLoanRequest(){
        for(int i=0;i<loanRequest.getLength()/2;i++){
            loanRequest.getValue(i).showLoanDetail();
        }
    }
    void writeLoan(ofstream &writeFile){
        int allLoanReq = loanRequest.getLength();
        writeFile.write((char *)(&allLoanReq),sizeof(allLoanReq));
        for(int i =0;i<allLoanReq ;i ++){
            loanRequest.getValue(i).writeToBin(writeFile);
        }
    }
    void readLoan(ifstream &readFile){
        int allLoanReq = 0;
        readFile.read((char *)(&allLoanReq), sizeof(allLoanReq));
        for (int i = 0; i < allLoanReq; i++) {
            Loan loan;
            loan.readBin(readFile);
            loanRequest.push(loan);
        }
    }
    // void addRequest(User &source,string text){
    //     string request = " - "+source.getName()+" "+source.getPhoneNumber()+" : \n"+"    "+text+". \n";
    //     userRequest.push_back(request);
    // }
    void writeToBinary(const string &fileName){
        ofstream writeFile(fileName, ios::trunc | ios::binary); 
        // writeVectorStr(writeFile,userRequest);
        writeLoan(writeFile);
        writeFile.close();
    }

    void readBin(const string &fileName){
        ifstream readFile(fileName, ios::binary);
        // readVectorStr(readFile,userRequest);
        readLoan(readFile);
        readFile.close();
    }
    // void showRequest(){
    //     for (auto request : userRequest) {
    //         cout << request << endl;
    //     }     
    //     cout << "----------------------------------------------------------------------------------------" << endl;
    // }
    // exchange rate
   double convertUSDtoKHR(double amountUSD, double exchangeRate) {
    if (amountUSD < 0) {
        throw invalid_argument("Amount in USD cannot be negative.");
    }
    if (exchangeRate <= 0) {
        throw invalid_argument("Exchange rate must be positive.");
    }
   
   }
    vector<Loan> getLoan(){
        return loanRequest;
    }
    void showLoanRequest(){
        for(auto i:loanRequest){
            i.showLoanDetail();
        }
    return amountUSD * exchangeRate;
}

double convertKHRtoUSD(double amountKHR, double exchangeRate, double deductionRate) {
    if (amountKHR < 0) {
        throw invalid_argument("Amount in KHR cannot be negative.");
    }
    if (exchangeRate <= 0) {
        throw invalid_argument("Exchange rate must be positive.");
    }
    if (deductionRate < 0 || deductionRate > 1) {
        throw invalid_argument("Deduction rate must be between 0 and 1.");
    }

    double amountUSD = amountKHR / exchangeRate;
    amountUSD -= amountUSD * deductionRate; // Apply deduction
    return amountUSD;
}

   
            
   void updateUserTotalMoney(User &user) {
    // Display the updated total money
     cout << "Updated User's Total Money:" << endl;
     user.getTotalMoneyKHR(); 
     user.getTotalMoneyUSD(); 
    
}
 void generateAdminReport(Bank &bank) {
    if (bank.getTotalUsers() == 0) {
        cout << "Error: No users to report!" << endl;
        return;
    }

    string customMessage;
    cout << "Enter a custom message for the report: ";
    cin.ignore(); // To handle any leftover newline characters in the input buffer
    getline(cin, customMessage); // Read the admin's custom message

    stringstream reportStream;

    // Add bank details to the report
    reportStream << "Bank Report\n";
    reportStream << "-------------------------\n";
    reportStream << "Total Users: " << bank.getTotalUsers() << "\n";
    reportStream << "Exchange Rate (USD to KHR): " << bank.getExchnageRate() << "\n";
    reportStream << "Admin Remarks: " << customMessage << "\n";


    bank.setReport(reportStream.str());

    
    cout << "Report successfully generated:\n";
    cout << reportStream.str();
}
 
    /*


    void setInterestRatesKHR(int durationInMonths, float interest) {
        bank->setInterestKHR(durationInMonths, interest);
        cout << "Set KHR interest for " << durationInMonths << " months to " << interest << "%.\n";
    } 

    void setInterestRatesUSD(int durationInMonths, float interest) {
        bank->setInterestUSD(durationInMonths, interest);
        cout << "Set USD interest for " << durationInMonths << " months to " << interest << "%.\n";
    }  


     */

    void displayInterestRates() {
        cout << "Interest Rates for KHR:" << endl;
        float* khrRates = bank->getInterestKHR();
        cout << "  3 Months: " << khrRates[0] << "%\n";
        cout << "  6 Months: " << khrRates[1] << "%\n";
        cout << "  9 Months: " << khrRates[2] << "%\n";
        cout << " 12 Months: " << khrRates[3] << "%\n";

        cout << "\nInterest Rates for USD:" << endl;
        float* usdRates = bank->getInterestUSD();
        cout << "  3 Months: " << usdRates[0] << "%\n";
        cout << "  6 Months: " << usdRates[1] << "%\n";
        cout << " 9 Months: " << usdRates[2] << "%\n";
        cout << " 12 Months: " << usdRates[3] << "%\n";
    }

};

#endif