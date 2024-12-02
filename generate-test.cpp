#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

std::string generateBankUserID(int branchCode ,int middleCount, int userCount ) {
    std::ostringstream userID;
    userID  
            << std::setw(3) << std::setfill('0') << branchCode   // 3-digit branch code
            << " "
            << std::setw(3) << std::setfill('0') << middleCount   // 3-digit branch code
            << " "
            << std::setw(3) << std::setfill('0') << userCount;  // 3-digit branch code

    return userID.str();
}

int main() {
    int maxDigit = 999;
    int branchCode = 110; 
    int middleCount = 000;
    int userCount = 1002;  

    while ( userCount > maxDigit) {

        if ( userCount > maxDigit ) middleCount ++ , userCount -= maxDigit ;

        if ( middleCount > maxDigit ) branchCode++ , userCount -= maxDigit ;

    }

    std::string userID = generateBankUserID(branchCode, middleCount, userCount);

    std::cout << "Generated Bank User ID: " << userID << std::endl;

    return 0;
}
