#include "ATM.hpp"
#include <iostream>
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
};

int main() {
    // Create a user account
    User user("John Doe", 100.0, 410000.0); // Initial balance: $100 and 410,000 KHR

    int choice;
    do {
        cout << "\n===== ATM Menu =====\n";
        cout << "1. Deposit\n";
        cout << "2. Withdraw\n";
        cout << "3. Exchange\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string currency;
            double amount;
            cout << "Enter currency (USD/KHR): ";
            cin >> currency;
            cout << "Enter amount: ";
            cin >> amount;
            ATM::deposit(user, amount, currency);
            break;
        }
        case 2: {
            string currency;
            double amount;
            cout << "Enter currency (USD/KHR): ";
            cin >> currency;
            cout << "Enter amount: ";
            cin >> amount;
            ATM::withdraw(user, amount, currency);
            break;
        }
        case 3: {
            string fromCurrency, toCurrency;
            double amount;
            cout << "Enter currency to exchange from (USD/KHR): ";
            cin >> fromCurrency;
            cout << "Enter currency to exchange to (USD/KHR): ";
            cin >> toCurrency;
            cout << "Enter amount: ";
            cin >> amount;
            ATM::exchange(user, amount, fromCurrency, toCurrency);
            break;
        }
        case 4:
            cout << "Exiting ATM. Thank you!\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
