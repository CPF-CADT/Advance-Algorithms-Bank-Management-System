#ifndef ATM_HPP
#define ATM_HPP

#include <iostream>
#include <string>
#include<fstream>
#include<sstream>
#include<vector>
#include "User.hpp"
using namespace std;

class ATM {
private:
    double totalMoneyUSD;
    double totalMoneyKHR;

public:
    ATM(double usd = 0.0, double khr = 0.0) : totalMoneyUSD(usd), totalMoneyKHR(khr) {}

void withdraw(User &user, double amount, const string &currency) {
    try {
        // Validate withdrawal amount
        if (amount <= 0) {
            throw runtime_error("Invalid withdrawal amount!");
        }

        // Handle USD withdrawals
        if (currency == "USD") {
            if (user.getTotalMoneyUSD() >= amount) {
                user.setTotalMoneyUSD(user.getTotalMoneyUSD() - amount);
                cout << "Withdrawal successful!" << endl;
                cout << "Remaining balance (USD): $" << user.getTotalMoneyUSD() << endl;
            } else {
                cout << "Insufficient USD balance!" << endl;
                char option;
                cout << "Do you want to deduct this amount from your KHR account instead? (y/n): ";
                cin >> option;

                if (option == 'y' || option == 'Y') {
                    if (user.getTotalMoneyKHR() >= amount) {
                        user.setTotalMoneyKHR(user.getTotalMoneyKHR() - amount);
                        cout << "Withdrawal successful!" << endl;
                        cout << "Amount deducted from KHR account." << endl;
                        cout << "Remaining balance (KHR): " << user.getTotalMoneyKHR() << " KHR" << endl;
                    } else {
                        throw runtime_error("Error: Insufficient KHR balance!");
                    }
                } else {
                    cout << "Withdrawal canceled by user." << endl;
                }
            }
        }
        // Handle KHR withdrawals
        else if (currency == "KHR") {
            if (user.getTotalMoneyKHR() >= amount) {
                user.setTotalMoneyKHR(user.getTotalMoneyKHR() - amount);
                cout << "Withdrawal successful!" << endl;
                cout << "Remaining balance (KHR): " << user.getTotalMoneyKHR() << " KHR" << endl;
            } else {
                cout << "Insufficient KHR balance!" << endl;
                // sleep(1);
                char option;
                cout << "Do you want to deduct this amount from your USD account instead? (y/n): ";
                cin >> option;

                if (option == 'y' || option == 'Y') {
                    if (user.getTotalMoneyUSD() >= amount) {
                        user.setTotalMoneyUSD(user.getTotalMoneyUSD() - amount);
                        cout << "Withdrawal successful!" << endl;
                        cout << "Amount deducted from USD account." << endl;
                        cout << "Remaining balance (USD): $" << user.getTotalMoneyUSD() << endl;
                    } else {
                        throw runtime_error("Error: Insufficient USD balance!");
                    }
                } else {
                    cout << "Withdrawal canceled by user." << endl;
                }
            }
        }
        // Invalid currency
        else {
            throw runtime_error("Error: Invalid currency type!");
        }
    } catch (const exception &e) {
        cerr << e.what() << endl;
    }
}


    void deposit(User &user, double amount, const string &currency) {
    try {
        // Validate deposit amount
        if (amount <= 0) {
            throw runtime_error("Invalid deposit amount!");
        }
        if (currency == "USD") {
            user.setTotalMoneyUSD(user.getTotalMoneyUSD() + amount);
            cout << "Deposit successful!" << endl;
            cout << "Updated balance (USD): $" << user.getTotalMoneyUSD() << endl;
        }
        else if (currency == "KHR") {
            user.setTotalMoneyKHR(user.getTotalMoneyKHR() + amount);
            cout << "Deposit successful!" << endl;
            cout << "Updated balance (KHR): " << user.getTotalMoneyKHR() << " KHR" << endl;
        }
        // Invalid currency
        else {
            throw runtime_error("Error: Invalid currency type!");
        }
    } catch (const exception &e) {
        cerr << e.what() << endl;
    }
}

    void checkBalance(User &user) {
        cout << "\nCurrent Balances:" << endl;
        cout << "USD: $" << user.getTotalMoneyUSD() << endl;
        cout << "KHR: " << user.getTotalMoneyKHR() << " KHR" << endl;
    }

    void stockATM(double usdAmount, double khrAmount) {
        totalMoneyUSD += usdAmount;
        totalMoneyKHR += khrAmount;
        cout << "Stocking successful!\nUpdated ATM stock:\n";
        cout << "USD: $" << totalMoneyUSD << endl;
        cout << "KHR: " << totalMoneyKHR << " KHR\n";
}
    void showATMBalance() const {
        cout << "\n*** ATM Balance ***\n";
        cout << "USD: $" << totalMoneyUSD << endl;
        cout << "KHR: " << totalMoneyKHR << " KHR\n";
    }

};
#endif