#include<iostream>
#include"../utils/arrayList.hpp"
#include"../utils/fileHandling.hpp"
#include"../utils/Admin.hpp"
#include "./User.hpp"
#define USER_FILE "user.dat"

std::string generateReport(ArrayList<User> &users) {
      updateTotals(users);

      // Get current date and time
      time_t now = time(0);
      char *dt = ctime(&now);

      std::ostringstream report;
      report << "Bank Report\n";
      report << "Date and Time: " << dt << "\n";
      report << "Total Users: " << totalUser << "\n";
      report << "Total Money (USD): $" << totalMoneyUSD << "\n";
      report << "Total Money (KHR): " << totalMoneyKHR << " KHR\n";
      report << "Exchange Rate (USD to KHR): " << exchangeRateUSDtoKHR << "\n\n";
      report << "User Details:\n";

      for (int i = 0; i < users.getLength(); i++) {
         User user = users.getValue(i);
         report << "User: " << user.getName() << " (Phone: " << user.getPhoneNumber() << ")\n";
         report << "  Balance (USD): $" << user.getTotalMoneyUSD() << "\n";
         report << "  Balance (KHR): " << user.getTotalMoneyKHR() << " KHR\n";
         report << "  Transaction History: " << user.getTransactionHistory() << "\n";
         report << "-----------------------------------------\n";
      }

      return report.str();
   }
int main(){
   ArrayList<User> users;
   Admin admin;
   readFromBinary(USER_FILE,users);
   string request;
   cout<<"Re : ";getline(cin,request);
   admin.addRequest(users.getValue(0),request);
   admin.showRequest();
   cout<<"Re : ";getline(cin,request);
   admin.addRequest(users.getValue(0),request);
   admin.showRequest();

   return 0;
}