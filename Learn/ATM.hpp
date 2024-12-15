#ifndef ATM_HPP
#define ATM_HPP

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>

using namespace std;

struct Transaction {
    string type;    // "Deposit" or "Withdraw"
    string currency; // "USD" or "KHR"
    double amount;
    string date;

    Transaction(string t, string c, double a, string d)
        : type(t), currency(c), amount(a), date(d) {}
};

class ATM {
private:
    vector<Transaction> history;

    string getCurrentDate() {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        stringstream ss;
        ss << 1900 + ltm->tm_year << "-" << setw(2) << setfill('0') << 1 + ltm->tm_mon
           << "-" << setw(2) << setfill('0') << ltm->tm_mday;
        return ss.str();
    }

public:
    void deposit(double &balanceUSD, double &balanceKHR, double amount, const string &currency) {
        if (amount <= 0) {
            cerr << "Error: Invalid deposit amount!" << endl;
            return;
        }

        if (currency == "USD") {
            if (amount < 100) {
                cerr << "Error: Minimum deposit for USD is $100." << endl;
                return;
            }
            balanceUSD += amount;
            cout << "Deposit successful! New USD Balance: $" << balanceUSD << endl;
        } else if (currency == "KHR") {
            if (amount < 400000) {
                cerr << "Error: Minimum deposit for KHR is 400,000 R." << endl;
                return;
            }
            balanceKHR += amount;
            cout << "Deposit successful! New KHR Balance: " << balanceKHR << " R" << endl;
        } else {
            cerr << "Error: Invalid currency!" << endl;
            return;
        }

        // Add to history
        history.emplace_back("Deposit", currency, amount, getCurrentDate());
    }

    void withdraw(double &balanceUSD, double &balanceKHR, double amount, const string &currency) {
        if (amount <= 0) {
            cerr << "Error: Invalid withdrawal amount!" << endl;
            return;
        }

        if (currency == "USD") {
            if (balanceUSD >= amount) {
                balanceUSD -= amount;
                cout << "Withdrawal successful! New USD Balance: $" << balanceUSD << endl;
            } else {
                cerr << "Error: Insufficient USD balance!" << endl;
                return;
            }
        } else if (currency == "KHR") {
            if (balanceKHR >= amount) {
                balanceKHR -= amount;
                cout << "Withdrawal successful! New KHR Balance: " << balanceKHR << " R" << endl;
            } else {
                cerr << "Error: Insufficient KHR balance!" << endl;
                return;
            }
        } else {
            cerr << "Error: Invalid currency!" << endl;
            return;
        }

        // Add to history
        history.emplace_back("Withdraw", currency, amount, getCurrentDate());
    }

    void showHistory() const {
        if (history.empty()) {
            cout << "No transaction history available.\n";
            return;
        }

        cout << "\n--- Transaction History ---\n";
        cout << left << setw(12) << "Type" << setw(8) << "Currency" << setw(10) << "Amount"
             << setw(12) << "Date" << endl;
        cout << string(40, '-') << endl;
        for (const auto &txn : history) {
            cout << left << setw(12) << txn.type << setw(8) << txn.currency
                 << setw(10) << txn.amount << setw(12) << txn.date << endl;
        }
    }
};

#endif
