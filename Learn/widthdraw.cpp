void withdraw(User &user, double amount, const string &currency, bool isAdmin) {
    try {
      
        if (!isAdmin) {
            int wrongAttempts = 0;
            string password;

            while (wrongAttempts < 3) {
                cout << "Enter Password: ";
                cin >> password;

                if (password == user.getPassword()) {
                    cout << "Login Successful..." << endl;
                    break; // Exit the password validation loop
                } else {
                    wrongAttempts++;
                    cout << "Incorrect Password!" << endl;
                }
            }
            if (wrongAttempts >= 3) {
                throw runtime_error("Too many incorrect attempts. Access denied!");
            }
        }
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
                cout << "Do you want to deduct this amount from your USD account instead? (y/n): ";
                cin >> option;

                if (option == 'y' || option == 'Y') {
                    if (user.getTotalMoneyUSD() >= amount) {
                        user.setTotalMoneyUSD(user.getTotalMoneyUSD() - amount);
                        cout << "Withdrawal successful!" << endl;
                        cout << "Amount deducted from USD account." << endl;
                        cout << "Remaining balance (USD): $" << user.getTotalMoneyUSD() << endl;
                    } else {
                        throw runtime_error("Error: Insufficient USD balance!");
                    }
                } else {
                    cout << "Withdrawal canceled by user." << endl;
                }
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
