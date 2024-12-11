#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "User.hpp" 

using namespace std;


// Function to withdraw money from the user's account based on their phone number
void withdraw(User &user, double amount, const string &currency) {
    try {
        if (currency == "USD") {
            
            if (amount <= 0) {
                throw runtime_error("Invalid withdrawal amount!");
            }
            if (user.getTotalMoneyUSD() >= amount) {
                
                user.setTotalMoneyUSD(user.getTotalMoneyUSD() - amount);
                cout << "Withdrawal successful!" << endl;
                cout << "Remaining balance (USD): $" << user.getTotalMoneyUSD() << endl;
            } else {
                throw runtime_error("Error: Insufficient USD balance!");
            }
        } else if (currency == "KHR") {
            
            if (amount <= 0) {
                throw runtime_error("Invalid withdrawal amount!");
            }
            if (user.getTotalMoneyKHR() >= amount) {
                
                user.setTotalMoneyKHR(user.getTotalMoneyKHR() - amount);
                cout << "Withdrawal successful!" << endl;
                cout << "Remaining balance (KHR): " << user.getTotalMoneyKHR() << " KHR" << endl;
            } else {
                throw runtime_error("Error: Insufficient KHR balance!");
            }
        } else {
            throw runtime_error("Error: Invalid currency type!");
        }
    } catch (const exception &e) {
        cerr << e.what() << endl;
    }
}

    