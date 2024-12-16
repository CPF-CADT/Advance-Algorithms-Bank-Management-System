#ifndef LOAN_HPP
#define LOAN_HPP
#include"Date.hpp"
#include"User.hpp"
#include"QRCode.hpp"
class Loan{
   private:
      QRCode amountLoan;
      string name;
      string reason;
      Date takeMoney;
      Date returnMoney;
      char phoneNumber[12];

   public:
        Loan(){
            reason = "NULL";
            strcpy(phoneNumber,"NULL");
            name = "NULL";
        }
        void applyLoan(User & users){
            amountLoan.cratePaymentCode();
            cin.ignore();
            cout<<"Reason : ";getline(cin,reason);
            cout<<"Return Date : \n";
            takeMoney.setCurrentDate();
            returnMoney.inputDate();
            strcpy(phoneNumber,users.getPhoneNumber());
            name = users.getName();
        }
        void writeToBin(ofstream &writeFile){
            writeFile.write((char *)(&amountLoan), sizeof(QRCode));    
            writeString(writeFile,name);
            writeString(writeFile,reason);
            writeFile.write((char *)(&takeMoney), sizeof(Date));    
            writeFile.write((char *)(&returnMoney), sizeof(Date)); 
            writeFile.write((char *)(&phoneNumber),sizeof(phoneNumber));  
        }
        void readBin(ifstream &readFile){
            readFile.read((char *)(&amountLoan), sizeof(QRCode));    
            name = readString(readFile);
            reason = readString(readFile);
            readFile.read((char *)(&takeMoney), sizeof(Date));    
            readFile.read((char *)(&returnMoney), sizeof(Date)); 
            readFile.read((char *)(&phoneNumber),sizeof(phoneNumber));  
        }
        void setReason(string& reasonValue) {
            reason = reasonValue;
        }
        void showLoanDetail(){
            cout << left << setw(20) << "Name" << setw(15) << "Phone" << endl;
            cout << "------------------------------------------------------------" << endl;
            cout << left << setw(20) << name << setw(15) << phoneNumber << endl;
            cout << endl;
            cout << "Loan Amount        : " <<amountLoan.getLoanData() << endl;
            cout << "Reason             : " << reason << endl;
            cout << "Take Money Date    : " << takeMoney.getDate() << endl;
            cout << "Return Money Date  : " << returnMoney.getDate() << endl;
        }
        void setPhoneNumber(char* phone) {
            strncpy(phoneNumber, phone, sizeof(phoneNumber) - 1);
            phoneNumber[sizeof(phoneNumber) - 1] = '\0';
        }
        void setName(string& nameValue) {
            name = nameValue;
        }
        string getReason() {
            return reason;
        }
        char* getPhoneNumber() {
            return phoneNumber;
        }
        string getName() {
            return name;
        }
<<<<<<< HEAD

        void payBackLoan(User& user) {
            try {
                // Advanced error checking and validation
                if (!amountLoan.isValidLoan()) throw runtime_error("Invalid loan details");

                // Extended date calculations with more precision
                int totalDays = takeMoney.daysBetween(returnMoney);
                
                // Validate loan duration
                if (totalDays <= 0) throw invalid_argument("Invalid loan duration");

                // Get loan amount with additional security checks
                double loanAmount = amountLoan.getLoanData();
                if (loanAmount <= 0) throw domain_error("Loan amount must be positive");

                // Dynamic interest rate calculation
                double baseInterestRate = 0.05; // Base 5% annual rate
                double dynamicInterestRate = calculateDynamicInterestRate(user, baseInterestRate);
                
                // Compound interest calculation
                double dailyInterestRate = dynamicInterestRate / 365.0;
                double compoundInterest = calculateCompoundInterest(loanAmount, dailyInterestRate, totalDays);
                
                // Late payment penalty
                double latePenalty = calculateLatePenalty(totalDays, loanAmount);
                
                // Total payback amount with penalties
                double totalPaybackAmount = loanAmount + compoundInterest + latePenalty;

                // Detailed loan payback breakdown
                displayLoanDetails(loanAmount, totalDays, dynamicInterestRate, 
                                compoundInterest, latePenalty, totalPaybackAmount);

                // Confirmation with advanced security
                if (!confirmPayback()) return "Loan payback cancelled.";

                // Multiple payment strategy
                PaybackStrategy paybackStrategy = determinePaybackStrategy(user, totalPaybackAmount);

                switch (paybackStrategy) {
                    case FULL_PAYMENT:
                        processFulLPayment(user, totalPaybackAmount);
                        break;
                    
                    case PARTIAL_PAYMENT:
                        processPartialPayment(user, totalPaybackAmount);
                        break;
                    
                    case LOAN_EXTENSION:
                        processLoanExtension(user, totalPaybackAmount);
                        break;
                    
                    case DEFAULT:
                        handleLoanDefault(user, totalPaybackAmount);
                        break;
                }
            }
            catch (const exception& e) {
                // Comprehensive error handling
                cerr << "Loan Payback Error: " << e.what() << endl;
                
                // Log error for system administrators
                logErrorToSystem(e.what());
                
                // Notify user with detailed error message
                notifyUserOfError(e.what());
            }
        }

        // Additional supporting functions (pseudo-code for demonstration)

        // Calculate dynamic interest rate based on user's credit history
        double calculateDynamicInterestRate(const User& user, double baseRate) {
            double creditScore = user.getCreditScore();
            double riskFactor = calculateRiskFactor(user);
            
            // Adjust interest rate based on credit score and risk
            return baseRate * (1 + (100 - creditScore) / 1000.0) * (1 + riskFactor);
        }

        // Compound interest calculation
        double calculateCompoundInterest(double principal, double dailyRate, int days) {
            return principal * (pow(1 + dailyRate, days) - 1);
        }

        // Late payment penalty calculation
        double calculateLatePenalty(int days, double loanAmount) {
            const double PENALTY_RATE = 0.01; // 1% daily penalty after due date
            int overdueDays = max(0, days - getLoanTermDays());
            return loanAmount * PENALTY_RATE * overdueDays;
        }

        // Determine best payback strategy
        PaybackStrategy determinePaybackStrategy(const User& user, double totalPaybackAmount) {
            double userBalance = user.getTotalMoneyUSD();
            
            if (userBalance >= totalPaybackAmount) return FULL_PAYMENT;
            
            if (userBalance > 0) return PARTIAL_PAYMENT;
            
            if (canExtendLoan(user)) return LOAN_EXTENSION;
            
            return DEFAULT;
        }

        // Detailed display of loan payback information
        void displayLoanDetails(double loanAmount, int days, double interestRate, 
                                double interest, double penalty, double totalPayback) {
            cout << "Comprehensive Loan Payback Details:" << endl;
            cout << "-----------------------------------" << endl;
            cout << "Original Loan Amount: $" << fixed << setprecision(2) << loanAmount << endl;
            cout << "Loan Duration: " << days << " days" << endl;
            cout << "Interest Rate: " << (interestRate * 100) << "%" << endl;
            cout << "Compound Interest: $" << interest << endl;
            cout << "Late Payment Penalty: $" << penalty << endl;
            cout << "Total Payback Amount: $" << totalPayback << endl;
        }

        bool isValidLoan() const {
            const double maxLoanAmount = 1000000.0;
            const int maxLoanDurationDays = 365;
            const double minInterestRate = 0.01;
            const double maxInterestRate = 0.2;

            // Check if the loan amount is within an acceptable range
            if (loanAmount <= 0 || loanAmount > maxLoanAmount) return false;
            
            // Ensure the loan duration is within allowed limits
            if (loanDurationDays <= 0 || loanDurationDays > maxLoanDurationDays) return false;
            
            // Validate the interest rate is within a reasonable range
            if (interestRate < minInterestRate || interestRate > maxInterestRate) return false;

            // Check that the borrower is eligible
            if (!borrower.isEligibleForLoan()) return false;

            // Additional checks (e.g., ensuring there are no overdue payments)
            if (hasOverduePayments || isBlacklisted) return false;
            
            return true; // Loan is valid
        }
        double getLoanData() const {
            return loanAmount;
        }

        // Calculate the number of days between two dates
        int daysBetween(const Date& start, const Date& end) const {
            return 30; // Example duration (30 days)
        }

=======
        QRCode & getAmountLoan(){
            return amountLoan;
        }
        Date getRetunDate(){
            return returnMoney;
        }
        Date getTakeDate(){
            return takeMoney;
        }
      
>>>>>>> 32eaea2fefbe8e54fdb73b0fb71630bae66ef3bc
};
#endif