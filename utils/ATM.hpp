#ifndef ATM_HPP
#define ATM_HPP

#include <iostream>
#include <string>
#include "User.hpp"
using namespace std;

class ATM {
private:
    double totalMoneyUSD; // USD balance
    double totalMoneyKHR; // KHR balance
    DepositInterest deposit; // DepositWithInterest object for managing deposits

public:
    ATM(double usd = 0.0, double khr = 0.0) : totalMoneyUSD(usd), totalMoneyKHR(khr) {}

    void withdraw(User &user, double amount, const string &currency) {
        try {
            if (amount <= 0) {
                throw runtime_error("Invalid withdrawal amount!");
            }
            if (currency == "USD") {
                if (user.getTotalMoneyUSD() >= amount) {
                    user.setTotalMoneyUSD(user.getTotalMoneyUSD() - amount);
                    cout << "Withdrawal successful!" << endl;
                    cout << "Remaining USD balance: $" << user.getTotalMoneyUSD() << endl;
                } else {
                    cout << "Insufficient USD balance!" << endl;
                }
            } else if (currency == "KHR") {
                if (user.getTotalMoneyKHR() >= amount) {
                    user.setTotalMoneyKHR(user.getTotalMoneyKHR() - amount);
                    cout << "Withdrawal successful!" << endl;
                    cout << "Remaining KHR balance: " << user.getTotalMoneyKHR() << " KHR" << endl;
                } else {
                    cout << "Insufficient KHR balance!" << endl;
                }
            } else {
                throw runtime_error("Invalid currency type!");
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
            cout << "1. Deposit with Interest" << endl;
            cout << "2. Withdraw" << endl;
            cout << "3. Check Balance" << endl;
            cout << "0. Exit" << endl;
            cout << "Enter your choice : ";
            cin >> choice;
            switch (choice) {
                case 1:
                    break;
                case 2:
                    cout << "Enter currency (USD/KHR): ";
                    cin >> currency;
                    cout << "Enter withdrawal amount: ";
                    cin >> amount;
                    withdraw(user, amount, currency);
                    break;
                case 3:
                    checkBalance(user);
                    break;
                case 0:
                    cout << "Exiting ATM. Thank you!" << endl;
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        } while (choice != 0);
    }
};

#endif
