#include "ATM.hpp"
#include <iostream>

using namespace std;

void showMenu() {
    cout << "\n--- ATM Menu ---\n";
    cout << "1. Deposit\n";
    cout << "2. Withdraw\n";
    cout << "3. Show Balances\n";
    cout << "4. Transaction History\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
}

string selectCurrency() {
    int currencyChoice;
    cout << "\nSelect currency:\n";
    cout << "1. USD\n";
    cout << "2. KHR\n";
    cout << "Enter your choice: ";
    cin >> currencyChoice;

    if (currencyChoice == 1) {
        return "USD";
    } else if (currencyChoice == 2) {
        return "KHR";
    } else {
        cerr << "Error: Invalid choice. Please select 1 (USD) or 2 (KHR).\n";
        return "";
    }
}

void handleDeposit(ATM &atm, double &balanceUSD, double &balanceKHR) {
    string currency = selectCurrency();
    if (currency.empty()) return; // Invalid currency selection

    double amount;
    cout << "Enter deposit amount: ";
    cin >> amount;

    atm.deposit(balanceUSD, balanceKHR, amount, currency);
}

void handleWithdraw(ATM &atm, double &balanceUSD, double &balanceKHR) {
    string currency = selectCurrency();
    if (currency.empty()) return; // Invalid currency selection

    double amount;
    cout << "Enter withdrawal amount: ";
    cin >> amount;

    atm.withdraw(balanceUSD, balanceKHR, amount, currency);
}

void showBalances(double balanceUSD, double balanceKHR) {
    cout << "\n--- Current Balances ---\n";
    cout << "USD Balance: $" << balanceUSD << "\n";
    cout << "KHR Balance: " << balanceKHR << " R\n";
}

int main() {
    ATM atm;
    double balanceUSD = 0.0, balanceKHR = 0.0;

    int choice;
    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                handleDeposit(atm, balanceUSD, balanceKHR);
                break;
            case 2:
                handleWithdraw(atm, balanceUSD, balanceKHR);
                break;
            case 3:
                showBalances(balanceUSD, balanceKHR);
                break;
            case 4:
                atm.showHistory();
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
