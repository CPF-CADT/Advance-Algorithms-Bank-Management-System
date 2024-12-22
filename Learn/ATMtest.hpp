#include<iostream>
#include"User.hpp"
#include"DepositWithInterest.hpp"


using namespace std;

class ATM {
private:
    double totalMoneyUSD;
    double totalMoneyKHR;
public:

    ATM() : totalMoneyUSD(0.0), totalMoneyKHR(0.0) {}  // Initialize balances to zero
    void withdraw(double amount, const string &currency) {
        try {
            if (amount <= 0) {
                throw runtime_error("Invalid withdrawal amount!");
            }
            if (currency == "USD") {
                if (totalMoneyUSD >= amount) {
                    totalMoneyUSD -= amount;
                    cout << "Withdrawal successful!" << endl;
                    cout << "Remaining balance (USD): $" << totalMoneyUSD << endl;
                } else {
                    cout << "Insufficient USD balance!" << endl;
                }
            } 
            else if (currency == "KHR") {
                if (totalMoneyKHR >= amount) {
                    totalMoneyKHR -= amount;
                    cout << "Withdrawal successful!" << endl;
                    cout << "Remaining balance (KHR): " << totalMoneyKHR << " KHR" << endl;
                } else {
                    cout << "Insufficient KHR balance!" << endl;
                }
            } 
            else {
                throw runtime_error("Error: Invalid currency type!");
            }
        } catch (const exception &e) {
            cerr << e.what() << endl;
        }
    }
    void checkBalance() {
        cout << "\nCurrent Balances:" << endl;
        cout << "USD Balance: $" << totalMoneyUSD << endl;
        cout << "KHR Balance: " << totalMoneyKHR << " KHR" << endl;
    }
    void displayMenu() {
        int choice;
        double amount;
        string currency;
        do {
            cout << "\n==================== ATM Menu ====================" << endl;
            cout << "1. Deposit with Interest" << endl;
            cout << "2. Withdraw" << endl;
            cout << "3. Check Balance" << endl;
            cout << "0. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch(choice) {
                case 1:
                    deposit.depositWithInterest(totalMoneyUSD, totalMoneyKHR);
                    break;
                case 2:
                    cout << "Enter the withdrawal amount: ";
                    cin >> amount;
                    cout << "Enter currency (USD/KHR): ";
                    cin >> currency;
                    withdraw(amount, currency);
                    break;
                case 3:
                    checkBalance();
                    break;
                case 0:
                    cout << "Exiting ATM. Thank you!" << endl;
                    break;
                default:
                    cout << "Invalid choice! Please try again." << endl;
                    break;
            }
        } while(choice != 0);
    }
};
int main() {
    ATM atm;
    atm.displayMenu();
    return 0;
}
