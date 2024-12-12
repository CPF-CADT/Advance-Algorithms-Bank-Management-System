void deposit(User &user, double amount, const string &currency, bool isAdmin) {
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
                    break; 
                } else {
                    wrongAttempts++;
                    cout << "Incorrect Password!" << endl;
                }
            }

            if (wrongAttempts >= 3) {
                throw runtime_error("Too many incorrect attempts. Access denied!");
            }
        }

        // Validate deposit amount
        if (amount <= 0) {
            throw runtime_error("Invalid deposit amount!");
        }

      
        if (currency == "USD") {
            user.setTotalMoneyUSD(user.getTotalMoneyUSD() + amount);
            cout << "Deposit successful!" << endl;
            cout << "Updated balance (USD): $" << user.getTotalMoneyUSD() << endl;
        }
      
        else if (currency == "KHR") {
            user.setTotalMoneyKHR(user.getTotalMoneyKHR() + amount);
            cout << "Deposit successful!" << endl;
            cout << "Updated balance (KHR): " << user.getTotalMoneyKHR() << " KHR" << endl;
        }
        // Invalid currency
        else {
            throw runtime_error("Error: Invalid currency type!");
        }
    } catch (const exception &e) {
        cerr << e.what() << endl;
    }
}
