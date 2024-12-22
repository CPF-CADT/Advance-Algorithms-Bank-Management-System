#include <iostream>
#include "ATM.hpp"

using namespace std;

int main() {
    // Initialize ATM with some initial balances
    ATM atm(100000.0, 5000.0); // Starting with 100,000 KHR and 5,000 USD
    cout << "Welcome to the ATM System!\n" << endl;

    // Display initial balances
    atm.displayBalance();

    // Menu for ATM operations
    int choice;
    do {
        cout << "\nATM Menu:" << endl;
        cout << "1. Deposit with Interest" << endl;
        cout << "2. Withdraw Money" << endl;
        cout << "3. Display ATM Balances" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "\nProcessing Deposit with Interest..." << endl;
                atm.depositWithInterest();
                break;
            }
            case 2: {
                double amount;
                string currency;
                cout << "\nEnter the withdrawal amount: ";
                cin >> amount;
                cout << "Enter the currency (KHR or USD): ";
                cin >> currency;
                atm.withdraw(amount, currency);
                break;
            }
            case 3: {
                atm.displayBalance();
                break;
            }
            case 0: {
                cout << "\nExiting the ATM. Thank you!" << endl;
                break;
            }
            default: {
                cout << "\nInvalid choice. Please try again." << endl;
            }
        }
    } while (choice != 0);

    return 0;
}
