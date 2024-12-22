#ifndef ATM_HPP
#define ATM_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "User.hpp"
#include <set>
using namespace std;
/// main between 56 to 282 lines
class ATM
{
private:
    double totalMoneyUSD;
    double totalMoneyKHR;
    set<double> validDenominationsUSD; // e.g., 10$, 50$, 100$
    set<double> validDenominationsKHR; // e.g., 10000, 50000, etc.

public:
    ATM(double usd = 0.0, double khr = 0.0) : totalMoneyUSD(usd), totalMoneyKHR(khr)
    {
        validDenominationsUSD = {10, 50, 100, 200};     // Example USD denominations
        validDenominationsKHR = {10000, 50000, 100000}; // Example KHR denominations
    }
    bool isValidDenominationUSD(double amount)
    {
        return validDenominationsUSD.find(amount) != validDenominationsUSD.end();
    }
    bool isValidDenominationKHR(double amount)
    {
        return validDenominationsKHR.find(amount) != validDenominationsKHR.end();
    }

    bool isDivisibleByValidDenominationsUSD(double amount) {
        for (double denomination : validDenominationsUSD) {
            if (static_cast<int>(amount) % static_cast<int>(denomination) == 0) {
                return true;
            }
        }
        return false; // No valid denomination found
    }

    bool isDivisibleByValidDenominationsKHR(double amount) {
        for (double denomination : validDenominationsKHR) {
            if (static_cast<int>(amount) % static_cast<int>(denomination) == 0) {
                return true; // Amount is divisible by at least one valid denomination
            }
        }
        return false; // No valid denomination found
    }
    

    void withdraw(User &user, double amount, const string &currency)
    {
        try
        {
            if (amount <= 0)
            {
                throw runtime_error("Invalid withdrawal amount!");
            }

            // Handle USD withdrawals
            if (currency == "USD")
            {
                if (!isDivisibleByValidDenominationsUSD(amount)) {
                    throw runtime_error("Invalid USD denomination! Amount must be 10$, 50$, or 100$.");
                }
                if (user.getTotalMoneyUSD() >= amount)
                {
                    user.setTotalMoneyUSD(user.getTotalMoneyUSD() - amount);
                    cout << "Withdrawal successful!" << endl;
                    cout << "Remaining balance (USD): $" << user.getTotalMoneyUSD() << endl;
                }
                else
                {
                    cout << "Insufficient USD balance!" << endl;
                    char option;
                    cout << "Do you want to deduct this amount from your KHR account instead? (y/n): ";
                    cin >> option;

                    if (option == 'y' || option == 'Y')
                    {
                        if (user.getTotalMoneyKHR() >= amount)
                        {
                            user.setTotalMoneyKHR(user.getTotalMoneyKHR() - amount);
                            cout << "Withdrawal successful!" << endl;
                            cout << "Amount deducted from KHR account." << endl;
                            cout << "Remaining balance (KHR): " << user.getTotalMoneyKHR() << " KHR" << endl;
                        }
                        else
                        {
                            throw runtime_error("Error: Insufficient KHR balance!");
                        }
                    }
                    else
                    {
                        cout << "Withdrawal canceled by user." << endl;
                    }
                }
            }
            // Handle KHR withdrawals
            else if (currency == "KHR")
            {   
                if (!isDivisibleByValidDenominationsKHR(amount)) {
                    throw runtime_error("Invalid KHR denomination! Amount must be 10000, 50000, or 100000 KHR.");
                }
                if (user.getTotalMoneyKHR() >= amount)
                {
                    user.setTotalMoneyKHR(user.getTotalMoneyKHR() - amount);
                    cout << "Withdrawal successful!" << endl;
                    cout << "Remaining balance (KHR): " << user.getTotalMoneyKHR() << " KHR" << endl;
                }
                else
                {
                    cout << "Insufficient KHR balance!" << endl;
                    // sleep(1);
                    char option;
                    cout << "Do you want to deduct this amount from your USD account instead? (y/n): ";
                    cin >> option;

                    if (option == 'y' || option == 'Y')
                    {
                        if (user.getTotalMoneyUSD() >= amount)
                        {
                            user.setTotalMoneyUSD(user.getTotalMoneyUSD() - amount);
                            cout << "Withdrawal successful!" << endl;
                            cout << "Amount deducted from USD account." << endl;
                            cout << "Remaining balance (USD): $" << user.getTotalMoneyUSD() << endl;
                        }
                        else
                        {
                            throw runtime_error("Error: Insufficient USD balance!");
                        }
                    }
                    else
                    {
                        cout << "Withdrawal canceled by user." << endl;
                    }
                }
            }
            // Invalid currency
            else
            {
                throw runtime_error("Error: Invalid currency type!");
            }
        }
        catch (const exception &e)
        {
            cerr << e.what() << endl;
        }
    }

    void deposit(User &user, double amount, const string &currency)
    {
        try
        {
            // Validate deposit amount
            if (amount <= 0)
            {
                throw runtime_error("Invalid deposit amount!");
            }
            if (currency == "USD")
            {   
                if (!isDivisibleByValidDenominationsUSD(amount)) {
                    throw runtime_error("Invalid USD denomination! Amount must be 10$, 50$, or 100$.");
                }
                user.setTotalMoneyUSD(user.getTotalMoneyUSD() + amount);
                cout << "Deposit successful!" << endl;
                cout << "Updated balance (USD): $" << user.getTotalMoneyUSD() << endl;
            }
            else if (currency == "KHR")
            {
                if (!isDivisibleByValidDenominationsKHR(amount)) {
                    throw runtime_error("Invalid KHR denomination! Amount must be 10000, 50000, or 100000 KHR.");
                }
                user.setTotalMoneyKHR(user.getTotalMoneyKHR() + amount);
                cout << "Deposit successful!" << endl;
                cout << "Updated balance (KHR): " << user.getTotalMoneyKHR() << " KHR" << endl;
            }
            // Invalid currency
            else
            {
                throw runtime_error("Error: Invalid currency type!");
            }
        }
        catch (const exception &e)
        {
            cerr << e.what() << endl;
        }
    }

    void checkBalance(User &user)
    {
        cout << "\nCurrent Balances:" << endl;
        cout << "USD: $" << user.getTotalMoneyUSD() << endl;
        cout << "KHR: " << user.getTotalMoneyKHR() << " KHR" << endl;
    }

    void stockATM(double usdAmount, double khrAmount)
    {
        totalMoneyUSD += usdAmount;
        totalMoneyKHR += khrAmount;
        cout << "Stocking successful!\nUpdated ATM stock:\n";
        cout << "USD: $" << totalMoneyUSD << endl;
        cout << "KHR: " << totalMoneyKHR << " KHR\n";
    }
    void showATMBalance() const
    {
        cout << "\n*** ATM Balance ***\n";
        cout << "USD: $" << totalMoneyUSD << endl;
        cout << "KHR: " << totalMoneyKHR << " KHR\n";
    }
    void waitForKeyPress()
    {
        cout << "\nPress Enter to return to the menu...";
        cin.ignore();
        cin.get();
    }
};
#endif