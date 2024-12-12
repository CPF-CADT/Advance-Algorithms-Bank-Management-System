void withdraw(User &user, double amount, const string &currency, bool isAdmin) {
    try {
        // Password validation for non-admin users
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
                throw runtime_error("Error: Insufficient USD balance!");
            }
        }
        // Handle KHR withdrawals
        else if (currency == "KHR") {
            if (user.getTotalMoneyKHR() >= amount) {
                user.setTotalMoneyKHR(user.getTotalMoneyKHR() - amount);
                cout << "Withdrawal successful!" << endl;
                cout << "Remaining balance (KHR): " << user.getTotalMoneyKHR() << " KHR" << endl;
            } else {
                throw runtime_error("Error: Insufficient KHR balance!");
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
