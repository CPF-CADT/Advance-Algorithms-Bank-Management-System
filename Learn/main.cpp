#include "ATM.hpp"
#include <iostream>
using namespace std;

int main() {
    // Create a User object
    User user("John Doe", 100.0, 410000.0); // Initial balances: $100 and 410,000 KHR

    int choice;
    do {
        cout << "\n--- ATM MENU ---\n";
        cout << "1. Deposit\n";
        cout << "2. Withdraw\n";
        cout << "3. Exchange\n";
        cout << "4. Display Balances\n";
        cout << "5. Transaction History\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int currencyChoice;
            double amount;
            cout << "Choose account: 1. USD 2. KHR\n";
            cin >> currencyChoice;
            cout << "Enter amount to deposit: ";
            cin >> amount;
            if (currencyChoice == 1) {
                ATM::deposit(user, amount, "USD");
            } else if (currencyChoice == 2) {
                ATM::deposit(user, amount, "KHR");
            } else {
                cout << "Invalid choice! Returning to main menu.\n";
            }
            break;
        }
        case 2: {
            int currencyChoice;
            double amount;
            cout << "Choose account: 1. USD 2. KHR\n";
            cin >> currencyChoice;
            cout << "Enter amount to withdraw: ";
            cin >> amount;
            if (currencyChoice == 1) {
                ATM::withdraw(user, amount, "USD");
            } else if (currencyChoice == 2) {
                ATM::withdraw(user, amount, "KHR");
            } else {
                cout << "Invalid choice! Returning to main menu.\n";
            }
            break;
        }
        case 3: {
            string fromCurrency, toCurrency;
            double amount;
            cout << "Enter currency to exchange from (USD/KHR): ";
            cin >> fromCurrency;
            cout << "Enter currency to exchange to (USD/KHR): ";
            cin >> toCurrency;
            cout << "Enter amount to exchange: ";
            cin >> amount;
            ATM::exchange(user, amount, fromCurrency, toCurrency);
            break;
        }
        case 4:
            user.displayBalances();
            break;
        case 5:
            ATM::displayHistory();
            break;
        case 6:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}
