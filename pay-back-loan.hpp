#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cmath>
using namespace std;

class Loan {
public:
    double loanAmount;
    int loanDurationDays;
    double interestRate;
    bool hasOverduePayments;
    bool isBlacklisted;
    User borrower;
    
    // Define the loan's validation methods
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
    
    // Assuming this function is called when fetching the loan amount
    double getLoanData() const {
        return loanAmount;
    }

    // Calculate the number of days between two dates
    int daysBetween(const Date& start, const Date& end) const {
        return 30; // Example duration (30 days)
    }
};

// Utility functions for loan validation and payback processing
bool isValidLoanDuration(int loanDurationDays) {
    const int MIN_LOAN_DURATION = 1;    // Minimum loan duration (in days)
    const int MAX_LOAN_DURATION = 365;  // Maximum loan duration (in days)

    // Check if the loan duration is within the valid range
    if (loanDurationDays < MIN_LOAN_DURATION || loanDurationDays > MAX_LOAN_DURATION) return false;

    return true;  // Loan duration is valid
}

bool isValidLoanAmount(double loanAmount) {
    const double MIN_LOAN_AMOUNT = 100.0;   // Minimum loan amount (e.g., $100)
    const double MAX_LOAN_AMOUNT = 1000000.0;  // Maximum loan amount (e.g., $1,000,000)

    // Check if the loan amount is within the valid range
    if (loanAmount < MIN_LOAN_AMOUNT || loanAmount > MAX_LOAN_AMOUNT) return false;

    return true;  // Loan amount is valid
}

double calculateDynamicInterestRate(const User& user, double baseRate) {
    double dynamicRate = baseRate;

    // Example: Increase rate based on user credit score
    if (user.getCreditScore() < 600) dynamicRate += 0.05;  // Higher interest rate for lower credit score
    else if (user.getCreditScore() > 750) dynamicRate -= 0.02;  // Discounted interest for higher credit score

    return dynamicRate;
}

double calculateCompoundInterest(double principal, double dailyRate, int days) {
    // Compound interest formula: A = P * (1 + r/n)^(nt)
    return principal * pow((1 + dailyRate), days) - principal;
}

double calculateLatePenalty(int overdueDays, double loanAmount) {
    double penaltyRate = 0.01;  // 1% per day for overdue payments
    if (overdueDays > 0) return loanAmount * penaltyRate * overdueDays;
    
    return 0.0;
}

// Error handling functions
void logErrorToSystem(const string& errorMessage) {
    ofstream logFile("loan_errors.log", ios::app);
    logFile << "Error: " << errorMessage << endl;
    logFile.close();
}

void notifyUserOfError(const string& errorMessage) {
    cout << "An error occurred: " << errorMessage << endl;
    cout << "Please contact customer support for assistance." << endl;
}

// Main loan repayment function
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

        // Validate loan amount
        if (!isValidLoanAmount(loanAmount)) throw domain_error("Loan amount must be between $100 and $1,000,000.");

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
        displayLoanDetails(loanAmount, totalDays, dynamicInterestRate, compoundInterest, latePenalty, totalPaybackAmount);

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

int main() {
    // Create user and loan objects to test the system
    User user;
    payBackLoan(user);  // Call the function
}
