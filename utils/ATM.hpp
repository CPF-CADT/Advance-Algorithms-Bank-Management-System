#ifndef ATM_HPP
#define ATM_HPP

#include <iostream>
#include <string>
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
                char option;
                // cout << "Do you want to deduct this amount from your USD account instead? (y/n): ";
                // cin >> option;

                // if (option == 'y' || option == 'Y') {
                //     if (user.getTotalMoneyUSD() >= amount) {
                //         user.setTotalMoneyUSD(user.getTotalMoneyUSD() - amount);
                //         cout << "Withdrawal successful!" << endl;
                //         cout << "Amount deducted from USD account." << endl;
                //         cout << "Remaining balance (USD): $" << user.getTotalMoneyUSD() << endl;
                //     } else {
                //         throw runtime_error("Error: Insufficient USD balance!");
                //     }
                // } else {
                //     cout << "Withdrawal canceled by user." << endl;
                // }
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

void displayMenu(User &user) {
    int choice;
    double amount;
    string currency;
    do {
        cout << "\n==================== ATM Menu ====================" << endl;
        cout << "1. Deposit" << endl;
        cout << "2. Withdraw" << endl;
        cout << "3. Check Balance" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "\nChoose currency for deposit:" << endl;
                cout << "1. KHR\n2. USD\nChoice: ";
                int currencyChoice;
                cin >> currencyChoice;
                currency = (currencyChoice == 1) ? "KHR" : "USD";
                cout << "Amount to deposit (" << currency << "): ";
                cin >> amount;
                deposit(user, amount, currency);
                break;
            }
            case 2: {
                cout << "\nChoose currency for withdrawal:" << endl;
                cout << "1. KHR\n2. USD\nChoice: ";
                int currencyChoice;
                cin >> currencyChoice;
                currency = (currencyChoice == 1) ? "KHR" : "USD";
                cout << "Amount to withdraw (" << currency << "): ";
                cin >> amount;
                withdraw(user, amount, currency);
                break;
            }
            case 3: {
                checkBalance(user);
                break;
            }
            case 0:{
                cout << "Exiting ATM menu." << endl;
            break;
            }               
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    
    } while (choice != 0);
}

};
#endif