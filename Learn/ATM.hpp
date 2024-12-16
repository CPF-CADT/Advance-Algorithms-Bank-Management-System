#ifndef ATM_HPP
#define ATM_HPP

#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

class User {
private:
    string name;
    double totalMoneyUSD;
    double totalMoneyKHR;

public:
    User(const string &name, double usd, double khr)
        : name(name), totalMoneyUSD(usd), totalMoneyKHR(khr) {}

    double getTotalMoneyUSD() const { return totalMoneyUSD; }
    double getTotalMoneyKHR() const { return totalMoneyKHR; }

    void setTotalMoneyUSD(double amount) { totalMoneyUSD = amount; }
    void setTotalMoneyKHR(double amount) { totalMoneyKHR = amount; }

    void displayBalances() const {
        cout << "Current Balances:\n";
        cout << "USD: $" << totalMoneyUSD << "\n";
        cout << "KHR: " << totalMoneyKHR << " KHR\n";
    }
};

class ATM {
public:
    static void deposit(User &user, double amount, const string &currency) {
        if (amount <= 0) {
            cerr << "Invalid deposit amount!\n";
            return;
        }

        if (currency == "USD") {
            user.setTotalMoneyUSD(user.getTotalMoneyUSD() + amount);
            cout << "Deposited $" << amount << " to USD account.\n";
        } else if (currency == "KHR") {
            user.setTotalMoneyKHR(user.getTotalMoneyKHR() + amount);
            cout << "Deposited " << amount << " KHR to KHR account.\n";
        } else {
            cerr << "Invalid currency type!\n";
        }
        user.displayBalances();
    }

    static void withdraw(User &user, double amount, const string &currency) {
        if (amount <= 0) {
            cerr << "Invalid withdrawal amount!\n";
            return;
        }

        if (currency == "USD") {
            if (user.getTotalMoneyUSD() >= amount) {
                user.setTotalMoneyUSD(user.getTotalMoneyUSD() - amount);
                cout << "Withdrew $" << amount << " from USD account.\n";
            } else {
                cerr << "Insufficient USD balance!\n";
            }
        } else if (currency == "KHR") {
            if (user.getTotalMoneyKHR() >= amount) {
                user.setTotalMoneyKHR(user.getTotalMoneyKHR() - amount);
                cout << "Withdrew " << amount << " KHR from KHR account.\n";
            } else {
                cerr << "Insufficient KHR balance!\n";
            }
        } else {
            cerr << "Invalid currency type!\n";
        }
        user.displayBalances();
    }

    static void exchange(User &user, double amount, const string &fromCurrency, const string &toCurrency) {
        const double exchangeRate = 4100.0; // 1 USD = 4100 KHR

        if (amount <= 0) {
            cerr << "Invalid exchange amount!\n";
            return;
        }

        if (fromCurrency == "USD" && toCurrency == "KHR") {
            if (user.getTotalMoneyUSD() >= amount) {
                user.setTotalMoneyUSD(user.getTotalMoneyUSD() - amount);
                user.setTotalMoneyKHR(user.getTotalMoneyKHR() + amount * exchangeRate);
                cout << "Exchanged $" << amount << " to " << amount * exchangeRate << " KHR.\n";
            } else {
                cerr << "Insufficient USD balance for exchange!\n";
            }
        } else if (fromCurrency == "KHR" && toCurrency == "USD") {
            double requiredKHR = amount * exchangeRate;
            if (user.getTotalMoneyKHR() >= requiredKHR) {
                user.setTotalMoneyKHR(user.getTotalMoneyKHR() - requiredKHR);
                user.setTotalMoneyUSD(user.getTotalMoneyUSD() + amount);
                cout << "Exchanged " << requiredKHR << " KHR to $" << amount << ".\n";
            } else {
                cerr << "Insufficient KHR balance for exchange!\n";
            }
        } else {
            cerr << "Invalid currency types for exchange!\n";
        }
        user.displayBalances();
    }
};

#endif
