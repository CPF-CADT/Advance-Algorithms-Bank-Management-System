#include "./utils/ATM.hpp"
#include "./utils/Admin.hpp"
#include "./utils/Bank.hpp"
#include "./utils/User.hpp"
#include "./utils/fileHandling.hpp"
#include <cstdlib>
#include <string>
#include <unistd.h>
#define DATA_USER "./Data/users.dat"
#define DATA_ADMIN "./Data/admin.dat"
#define BANK_USER "./Data/bank.dat"
#define DATA_ATM "./Data/atm.dat"

// char* comfirmPassword();
void clearScreen(){
   #ifdef _WIN32
      system("cls");
   #else
      system("clear");
   #endif
}
void puseScreen() {
#ifdef _WIN32
   system("pause");
#else
   fflush(stdout); // Ensure the message is printed before waiting for input
   getchar();
#endif
}
bool enterPassword(User user);
int displayOption(string *allOption, int size);
void header(const string header);
int main() {
   int option;
   string mainOption[] = {"ATM", "User", "Administration"};
   string userLoginOption[] = {"Login", "Register"};
   string userInterface[] = {"Check Balance", "Transaction History", "Transfer Money", "Payment",
                             "Deposit with Interest", "Loan", "Update Information", "Check Information Detail", "Request to Admin"};
   string transferOption[] = {"Transfer to Own Account", "Transfer to Other Account"};
   string payment[] = {"Create A payment code ", "Pay money"};
   string adminInterface[] = {
       "Create User Account", "Deposit", "Withdraw",
       "Search User Information", "Approve Loan", "Check Request",
       "Update Bank Data", "UnBlock User", "Block User",
       "Pay Loan", "Write Report", "Bank Information"};
   string createAccount[] = {"Create User Account", "Create Many Account"};
   Bank bank;
   ATM atm;
   Admin admin;
   ArrayList<User> users;
   User newUser;
   User adminUser;
   int currentIndexUser = -1;

   // Load data to use
   bank.setExchnageRate(4100.00);
   readFromBinary(DATA_USER, users);
   admin.readBin(DATA_ADMIN);
   // admin.payInterest(users);
   do {
   START:
      clearScreen();
      header("KON KHMER BANK");
      switch (displayOption(mainOption, 3)) {
         case 1: {
         // ATM
         mainATM:
            clearScreen();
            int choices;
            cout << "\n==================== ATM Menu ====================" << endl;
            cout << "1. ATM Machine" << endl;
            cout << "2. For Stuff" << endl;
            cout << "0. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> choices;
            switch (choices) {
            case 1: {
            // ATM
            atminterface:
               clearScreen();
               char phone[12], password[16];
               cout << "Enter Information to Login" << endl;
               cout << "Phone number: ";
               cin >> phone;
               try{
                  currentIndexUser = indexOfUser(phone, users);
               }catch(exception &e){
                  cerr<<"User Not Found..!"<<endl;
               }
               if (currentIndexUser != -1) {
                  cin.ignore();
                  if (enterPassword(users.getValue(currentIndexUser))) {
                     // cout << "Login success ..." << endl;
                     // Display ATM Menu
                     User user;
                     int choice;
                     double amount;
                     string currency;
                     do {
                        cout << "\n==================== ATM ====================" << endl;
                        cout << "1. Deposit" << endl;
                        cout << "2. Withdraw" << endl;
                        // cout << "3. Check Balance" << endl;
                        cout << "0. Exit" << endl;
                        cout << "Enter your choice:  ";
                        cin >> choice;
                        switch (choice) {
                        case 1: {
                           clearScreen();
                           cout << "\nChoose currency for deposit:" << endl;
                           cout << "1. KHR\n2. USD\nChoice: ";
                           int currencyChoice;
                           cin >> currencyChoice;
                           currency = (currencyChoice == 1) ? "KHR" : "USD";
                           cout << "Amount to deposit (" << currency << "): ";
                           cin >> amount;
                           atm.deposit(user, amount, currency);
                           atm.waitForKeyPress();
                           clearScreen();
                           writeToBinary(DATA_USER,users);
                           break;
                        }
                        case 2: {
                           clearScreen();
                           cout << "\nChoose currency for withdrawal:" << endl;
                           cout << "1. KHR\n2. USD\nChoice: ";
                           int currencyChoice;
                           cin >> currencyChoice;
                           currency = (currencyChoice == 1) ? "KHR" : "USD";
                           cout << "Amount to withdraw (" << currency << "): ";
                           cin >> amount;
                           atm.withdraw(user, amount, currency);
                           sleep(2);
                           atm.waitForKeyPress();
                           clearScreen();
                           writeToBinary(DATA_USER,users);
                           break;
                        }
                        // case 3: {
                        //    clearScreen();
                        //    cout << "\n==================== User Balance ====================" << endl;
                        //    atm.checkBalance(user);
                        //    // puseScreen();
                        //    atm.waitForKeyPress();
                        //    goto mainATM;
                        //    break;
                        // }
                        case 0: {
                           clearScreen();
                           cout << "Exiting ATM menu." << endl;
                           sleep(1);
                           goto mainATM;
                           break;
                        }
                        default: {
                           cout << "Invalid choice! Please try again." << endl;
                           goto START;
                        }
                        }
                     } while (choice != 0);
                  }
               } else {
                  cout << "User not found!" << endl;
                  sleep(0.3);
                  cout << " -> Try again!" << endl;
                  sleep(1);
                  goto atminterface;
               }
               break;
            }
            case 2: {
            atmBalance:
               clearScreen();
               int option;
               cout << "\n==================== ATM Balance ====================" << endl;
               cout << "1. Stock USD" << endl;
               cout << "2. Stock KHR" << endl;
               cout << "3. Check Balance" << endl;
               cout << "0. Exit" << endl;
               cout << "Enter : ";
               cin >> option;
               switch (option) {
               case 1: {
                  cout << "\n==================== Stock in USD ====================" << endl;
                  string password;
                  cout << "Enter admin password: ";
                  cin >> password;
                  if (password == "admin123") {
                     double usdAmount;
                     cout << "Enter amount to stock in USD: ";
                     cin >> usdAmount;
                     if (usdAmount < 0) {
                        cerr << "Invalid USD amount! Must be non-negative." << endl;
                        atm.waitForKeyPress();
                        break;
                     }
                     atm.stockATM(usdAmount, 0);
                     atm.showATMBalance();
                     atm.waitForKeyPress();
                  } else {
                     cout << "Access denied. Incorrect password!" << endl;
                     atm.waitForKeyPress();
                  }
                  break;
               }

               case 2: {
                  cout << "\n==================== Stock in KHR ====================" << endl;
                  string password;
                  cout << "Enter admin password: ";
                  cin >> password;
                  if (password == "admin123") {
                     double khrAmount;
                     cout << "Enter amount to stock in KHR: ";
                     cin >> khrAmount;
                     if (khrAmount < 0) {
                        cerr << "Invalid KHR amount! Must be non-negative." << endl;
                        atm.waitForKeyPress();
                        break;
                     }
                     atm.stockATM(0, khrAmount);
                     atm.waitForKeyPress();
                  } else {
                     cout << "Access denied. Incorrect password!" << endl;
                     atm.waitForKeyPress();
                  }
                  break;
               }
               case 3: {
                  cout << "\n==================== Stock in USD ====================" << endl;
                  string password;
                  cout << "Enter admin password: ";
                  cin >> password;
                  if (password == "admin123") {
                     clearScreen();
                     cout << "Exiting ATM balance." << endl;
                     atm.showATMBalance();
                     atm.waitForKeyPress();
                     goto mainATM;
                  } else {
                     cout << "Access denied. Incorrect password!" << endl;
                     atm.waitForKeyPress();
                  }
                  goto atmBalance;
                  break;
               }
               case 0: {
                  clearScreen();
                  cout << "Exiting ATM balance." << endl;
                  sleep(1);
                  goto mainATM;
                  break;
               }
               default: {
                  cout << "Invalid choice! Please try again." << endl;
                  goto START;
                  break;
               } break;
               }
            case 0:
               clearScreen();
               goto START;
               break;
            default:
               cout << endl;
               clearScreen();
               cout << endl;
               cout << "ATM Bot : Nuh uh!! " << endl;
               sleep(1);
               cout << "ATM Bot : Incorrected input. Try again!! (2) " << endl;
               sleep(1);
               goto mainATM;
               break;
            } break;
            }
         }
         case 2:
         USER:
            clearScreen();
            header("USER INTERFACE");
            option = displayOption(userLoginOption, 2);
            switch (option) {
            case 1:
               char phone[12], password[16];
               clearScreen();
               // for(int i=0;i<users.getLength();i++){
               //    users.getValue(i).output();
               // }
               cout << " Enter Information to Login" << endl;
               cout << "Phone number : ";
               cin >> phone;
               try{
                  currentIndexUser = indexOfUser(phone, users);
               }catch(exception &e){
               }
               if (currentIndexUser != -1) {
                  cin.ignore();
                  if (enterPassword(users.getValue(currentIndexUser))) {
                     cout << "Login success ..." << endl;
                  // apply some animetion
                  userInterface:
                     clearScreen();
                     header("USER ACCOUNT");
                     Date cur;
                     users.getValue(currentIndexUser).payInterest(cur);
                     int op;
                     cout << "Welcome back " << users.getValue(currentIndexUser).getFirstName() << endl;
                     op = displayOption(userInterface, 9);
                     switch (op) {
                     // Code
                     case 1: {
                        // Code Show Money of user
                        clearScreen();
                        header("USER BALANCE");
                        users.getValue(currentIndexUser).showBalance();
                        cout << "Press anykey Exit ... " << endl;
                        cin.ignore();
                        puseScreen();
                        break;
                     }
                     case 2:
                        clearScreen();
                        header("TRANSACTION HISTORY");
                        // Code Transaction History
                        for (string i : users.getValue(currentIndexUser).getHistoryTransaction()) {
                           cout << i;
                        }
                        cout << "Press anykey Exit ... " << endl;
                        cin.ignore();
                        puseScreen();
                        break;
                     case 3:
                        // Code transfer money ACLIDA Concept
                        clearScreen();
                        header("TRANSFER MONEY");
                        switch (displayOption(transferOption, 2)) {
                        case 1: {
                           clearScreen();
                           header("TRANSFER TO OWN ACCOUNT");
                           users.getValue(currentIndexUser).transferOwnAccount(bank.getExchnageRate());
                           // need to write
                           break;
                        } 
                        case 2: {
                           // destination User
                           clearScreen();
                           header("TRANSFER TO OTHER ACCOUNT");
                           char phone[12];
                           cout << "Phone Number : ";
                           cin >> phone;
                           User &destUser = users.getValue(indexOfUser(phone, users));
                           users.getValue(currentIndexUser).transferToOtherAccount(destUser, bank.getExchnageRate());
                           writeToBinary(DATA_USER, users);
                           break;
                        }
                        case 0: {
                           goto userInterface;
                           break;
                        }
                        cout << "Press anykey Exit ... " << endl;
                        cin.ignore();
                        puseScreen();
                        break;
                        }
                     case 4:
                        // Code payment
                        clearScreen();
                        header("PAYMENT TRANSACTION");
                        switch (displayOption(payment, 2)) {
                        case 1:
                           users.getValue(currentIndexUser).addQR();
                           writeToBinary(DATA_USER, users);
                           break;
                        case 2: {
                           users.getValue(currentIndexUser).payMoney(users, currentIndexUser);
                           writeToBinary(DATA_USER, users);
                           break;
                        }
                        case 0: {
                           goto userInterface;
                           break;
                        }
                        }
                        cout << "Press anykey Exit ... " << endl;
                        cin.ignore();
                        puseScreen();
                        break;
                     case 5:
                        // Code Deposit with Interest
                        clearScreen();
                        header("DEPOSIT WITH INTEREST");
                        try {
                           users.getValue(currentIndexUser).addDepositWithInterest(bank);
                           admin.addlistUserDeposit((string)users.getValue(currentIndexUser).getPhoneNumber());
                           writeToBinary(DATA_USER, users);
                           admin.writeToBinary(DATA_ADMIN);
                        } catch (exception &e) {
                           cerr << e.what();
                        }
                        cout << "Press anykey Exit ... " << endl;
                        cin.ignore();
                        puseScreen();
                        break;
                     case 6:
                        // Code Apply Loan
                        clearScreen();
                        header("APPLY FOR LOAN");
                        // check loan is exit or not
                        if (!users.getValue(currentIndexUser).isHaveLoan()) {
                           Loan loan;
                           loan.applyLoan(users.getValue(currentIndexUser), bank);
                           admin.requestLoan(loan);
                           admin.writeToBinary(DATA_ADMIN);
                           // write admin
                        } else {
                           cout << "You Have Loan. Need pay back money to Loan again" << endl;
                        }
                        cout << "Press anykey Exit ... " << endl;
                        cin.ignore();
                        puseScreen();
                        break;
                     case 7:
                        clearScreen();
                        header("UPDATE USER INFORMATION ");
                        // Code Update Information
                        users.getValue(currentIndexUser).updateUserInfo();
                        writeToBinary(DATA_USER, users);
                        break;
                     case 8:
                        // Code Check Information Detail
                        clearScreen();
                        users.getValue(currentIndexUser).displayInfo();
                        cin.ignore();
                        cout << "Press anykey Exit ... " << endl;
                        puseScreen();
                        break;
                     case 9: {
                        // Code Request to Admin
                        string request;
                        Date date;
                        cin.ignore();
                        header("SENT REQUEST ");
                        cout << "Enter Request : ";
                        getline(cin, request);
                        date.setCurrentDate();
                        request = request + "\n\n" + date.getDate();
                        admin.addRequest(users.getValue(currentIndexUser), request);
                        admin.showRequest();
                        // ned to sacve to admin
                        cout << "Press anykey Exit ... " << endl;
                        cin.ignore();
                        puseScreen();
                        break;
                     }
                     case 0: {
                        goto USER;
                        break;
                     }
                     }

                     goto userInterface;
                  }
               } else {
                  currentIndexUser = -1;
                  cout << "User Not Found" << endl;
                  sleep(1);
                  goto USER;
               }
               break;
            case 2: {
               clearScreen();
               // header("Create User Account");
               newUser.input(DATA_USER);
               if (users.getLength() > 0) {
                  try {
                     if (newUser.findFreeOrder(users, newUser) == users.getLength()) {
                        users.push(newUser);
                     } else {
                        users.insertAt(newUser.findFreeOrder(users, newUser), newUser);
                     }
                  } catch (exception &e) {
                     cerr << e.what();
                  }
               } else {
                  users.push(newUser);
               }
               writeToBinary(DATA_USER, users);
               cout << "Success" << endl;
               cout << "Press anykey Exit ... " << endl;
               cin.ignore();
               puseScreen();
               goto USER;
               break;
            }
            case 0:{
               // exit
               goto START;
               break;
            }
            
            break;
         }
         case 3:
            ADMIN_INTER:
            clearScreen();
            header("KON KHMER BANK ADMINSTRATION");
            switch (displayOption(adminInterface, 12)) {
            case 1:
               clearScreen();
               header("Create User Account");
               switch (displayOption(createAccount, 2)) {
               case 1: {
                  // header("Create Account");
                  User newUser;
                  newUser.input(DATA_USER);
                  if (users.getLength() > 0) {
                     try {
                        if (newUser.findFreeOrder(users, newUser) == users.getLength()) {
                           users.push(newUser);
                        } else {
                           users.insertAt(newUser.findFreeOrder(users, newUser), newUser);
                        }
                     } catch (exception &e) {
                        cerr << e.what();
                     }
                  } else {
                     users.push(newUser);
                  }
                  writeToBinary(DATA_USER, users);
                  cout << "Success" << endl;
                  cout << "Press anykey Exit ... " << endl;
                  cin.ignore();
                  puseScreen();
                  break;
               }
               case 2: {
                  header("Create Many Account");
                  string fileName;
                  cout << "Enter File CSV : ";
                  cin >> fileName;
                  readFromCV(fileName, users, DATA_USER);
                  cout << "Press anykey Exit ... " << endl;
                  cin.ignore();
                  puseScreen();
                  break;
               }
               case 0: {
                  goto ADMIN_INTER;
                  break;
               }

            break;
            }
            case 2: {
               clearScreen();
               char phone[12];
               QRCode deposit;
               header("Deposit");
               cout << "Phone Number : ";
               cin >> phone;
               int indexUser;
               try {
                  indexUser = indexOfUser(phone, users);
                  // use input password
               } catch (exception &e) {
                  cerr << e.what();
               }
               if (indexUser != -1) {
                  deposit.cratePaymentCode();
                  if (deposit.getAmountKHR() > 0) {
                     admin.deposit(users.getValue(indexUser), deposit.getAmountKHR(), "KHR");
                     users.getValue(indexUser).addHistoryTransaction(users.getValue(indexUser).logTransactionReceiveFromBank(deposit.getAmountKHR(), false));
                     cout<<"Transaction Success....!"<<endl;
                  } else {
                     admin.deposit(users.getValue(indexUser), deposit.getAmountUSD(), "USD");
                     users.getValue(indexUser).addHistoryTransaction(users.getValue(indexUser).logTransactionReceiveFromBank(deposit.getAmountUSD(), true));
                     cout<<"Transaction Success....!"<<endl;
                  }
               }
               writeToBinary(DATA_USER, users);
               cin.ignore();
               puseScreen();
               break;
            }
            case 3: {
               clearScreen();
               header("Withdraw");
               char phone[12];
               QRCode withdraw;
               cout << "Phone Number : ";
               cin >> phone;
               int indexUser;
               try {
                  indexUser = indexOfUser(phone, users);
               } catch (exception &e) {
                  cerr << e.what();
               }
               if (indexUser != -1) {
                  withdraw.cratePaymentCode();
                  if (withdraw.getAmountKHR() > 0) {
                     admin.withdraw(users.getValue(indexUser), withdraw.getAmountKHR(), "KHR");
                     users.getValue(indexUser).addHistoryTransaction(users.getValue(indexUser).logTransactionWithdraw(withdraw.getAmountKHR(), false));
                     cout<<"Transaction Success....!"<<endl;
                  } else {
                     admin.withdraw(users.getValue(indexUser), withdraw.getAmountUSD(), "USD");
                     users.getValue(indexUser).addHistoryTransaction(users.getValue(indexUser).logTransactionWithdraw(withdraw.getAmountUSD(), true));
                     cout<<"Transaction Success....!"<<endl;
                  }
               }
               writeToBinary(DATA_USER, users);
               cin.ignore();
               puseScreen();
               break;
            }
            case 4: {
               clearScreen();
               char phone[12];
               header("Search User Information");
               cout << "Phone number :";
               cin >> phone;
               try {
                  admin.searchUserInformation(phone, users);
               } catch (exception &e) {
                  cerr << e.what();
               }
               cin.ignore();
               puseScreen();
               break;
            }
            case 5:{
               clearScreen();
               header("Approve Loan");
               cout << "ALL Loan Request"<<endl;
               admin.showLoanRequest();
               int code;
               int indexOfloan;
               char choice;
               again:
               cout << "\n====================================================="<<endl;
               cout<<"Input the code to aprove :"; cin>>code;
               for(int i=0;i< admin.getLoan().getLength();i++){
                     if(code == admin.getLoan().getValue(i).getAmountLoan().getCode() ){
                        admin.getLoan().getValue(i).showLoanDetail();
                        cout<<"Is it a right one? (Y/N)";cin>>choice;
                        switch (choice){
                        case 'Y':{
                        // char* phone=l.getPhoneNumber();
                        try{
                           /* code */
                        
                        int index = indexOfUser(admin.getLoan().getValue(i).getPhoneNumber(),users);
                        if(admin.getLoan().getValue(i).getAmountLoan().getAmountKHR()>0){
                           users.getValue(index).addMoneyKHR(admin.getLoan().getValue(i).getAmountLoan().getAmountKHR());
                           users.getValue(index).addLoanMoneyKHR(admin.getLoan().getValue(i).getAmountWithInterest());
                           users.getValue(index).addHistoryTransaction(users.getValue(index).logTransactionReceiveFromBank(admin.getLoan().getValue(i).getAmountLoan().getAmountKHR(),false));
                           writeToBinary(DATA_USER,users);           
                        }else {
                           users.getValue(index).addMoneyUSD(admin.getLoan().getValue(i).getAmountLoan().getAmountUSD());
                           users.getValue(index).addLoanMoneyUSD(admin.getLoan().getValue(i).getAmountWithInterest());
                           users.getValue(index).addHistoryTransaction(users.getValue(index).logTransactionReceiveFromBank(admin.getLoan().getValue(i).getAmountLoan().getAmountUSD(),true));
                           writeToBinary(DATA_USER,users);           
                        }
                        cout<<"Loan approve success!!"<<endl;
                        admin.getListLoanUser().push(admin.getLoan().getValue(i));
                        admin.getLoan().removeAt(i);
                        admin.writeToBinary(DATA_ADMIN);
                        writeToBinary(DATA_USER,users);           
                        }catch(const std::exception& e){
                           std::cerr << e.what() << '\n';
                        }
                        break;
                        }
                        case 'N':{
                           cout<<"Okey"<<endl;
                           goto ADMIN_INTER;
                           }
                        }
                     }
                  }
               cin.ignore();
               puseScreen();
               goto ADMIN_INTER;
               break;
            }
            case 6:
               clearScreen();
               header("Check Request");
               admin.readBin(DATA_ADMIN);
               admin.showRequest();
               cin.ignore();
               puseScreen();
               goto ADMIN_INTER;
               break;
            case 7:
               clearScreen();
               header("Update Bank Data");
               cin.ignore();
               puseScreen();
               goto ADMIN_INTER;
               break;
            case 8:
               clearScreen();
               header("Un Block User");
               admin.unblockUser(users);
               admin.writeToBinary(DATA_ADMIN);
               writeToBinary(DATA_USER,users);
               cin.ignore();
               puseScreen();
               goto ADMIN_INTER;
               break;
            case 9:
               clearScreen();
               header("Block User");
               char phone[16];
               cout<<"Phone Number : ";cin>>phone;
               admin.blockUserAccount(phone,users);
               admin.writeToBinary(DATA_ADMIN);
               writeToBinary(DATA_USER,users);
               cin.ignore();
               puseScreen();
               goto ADMIN_INTER;
               break;
            case 10:{
               clearScreen();
               header("Pay Loan");
               char phoneNum[16];
               string confirm;
               double amountKHR;
               double amountUSD;
               int curIndex;
               cout << "Phone number : ";
               cin >> phoneNum;
               for(int i=0;i<admin.getListLoanUser().getLength();i++){
               if(strcmp(phoneNum,admin.getListLoanUser().getValue(i).getPhoneNumber())==0){
                  curIndex = indexOfUser(phoneNum,users);
                  users.getValue(curIndex).output();
                  admin.getListLoanUser().getValue(i).listPayBack();
                  cout<<"Press Yes to pay : ";cin>>confirm;
                  if(confirm=="Yes" || confirm == "yes"){
                     if(curIndex!=-1){
                        amountKHR = admin.getListLoanUser().getValue(i).getAmountLoan().getAmountKHR();
                        if(amountKHR>0){
                           cout<<"Amount : "<<admin.getListLoanUser().getValue(i).payBack(users.getValue(curIndex))<<" R "<<endl;
                           // users.getValue(curIndex).setLoanKHR(users.getValue(curIndex).getLoanKHR()-amountKHR);
                           users.getValue(curIndex).addHistoryTransaction(users.getValue(curIndex).logTransactionWithdraw(amountKHR,false));
                        }else{
                           cout<<"Amount : "<<admin.getListLoanUser().getValue(i).payBack(users.getValue(curIndex))<<" $ "<<endl;
                           amountUSD = admin.getListLoanUser().getValue(i).getAmountLoan().getAmountKHR();
                           // users.getValue(curIndex).setLoanUSD(users.getValue(curIndex).getLoanUSD()-amountUSD);
                           users.getValue(curIndex).addHistoryTransaction(users.getValue(curIndex).logTransactionWithdraw(amountUSD,true));
                        }
                        if(users.getValue(curIndex).getLoanKHR() == 0 && users.getValue(curIndex).getLoanUSD() == 0 ){
                           try{
                              admin.getListLoanUser().removeAt(i);
                           }catch(exception &e){
                              cerr<<e.what()<<endl;
                           }
                        }
                        admin.getListLoanUser().getValue(i).listPayBack();
                        admin.writeToBinary(DATA_ADMIN);
                        writeToBinary(DATA_USER,users);
                        users.getValue(curIndex).showBalance();
                     }else{
                        cout<<"User Not Foud"<<endl;
                     }
                  }else{
                     cout<<"Cancle Porcess"<<endl;
                  }
                  }
               }
               admin.writeToBinary(DATA_ADMIN);
               writeToBinary(DATA_USER,users);
               cin.ignore();
               puseScreen();
               goto ADMIN_INTER;
               break;
               }
            case 11:
               clearScreen();
               header("Write Report");
               admin.generateAdminReport(bank);
               admin.writeToBinary(DATA_ADMIN);
               cin.ignore();
               puseScreen();
               goto ADMIN_INTER;
               break;
            case 12:
               clearScreen();
               header("Bank Information");
               admin.readBin(DATA_ADMIN);
               admin.displayInterestRates(bank);
               cin.ignore();
               puseScreen();
               goto ADMIN_INTER;
               break;
            case 0:{
               goto START;
            break;}
            default:
               cout << "Invalid Input " << endl;
               break;
         }
         break;
         case 0:
            clearScreen();
            cout << "Thank You" << endl;
         break;
      } 
   }while (option != 0);
   return 0;
};
void header(const string header) {
   cout << "=========================================" << endl;
   cout << "         " << header << endl;
   cout << "=========================================" << endl
        << endl;
}
int displayOption(string *allOption, int size) {
   string op;
   int choise;
   for (int i = 1; i <= size; i++) {
      cout << i << " . " << (allOption[i - 1]) << endl;
   }
   cout << "0 . Exit " << endl;
   cout << "Choose : ";
   cin >> op;
   try {
      choise = stoi(op);
      return choise;
   } catch (invalid_argument &e) {
      cerr << "Input Must be a number" << endl;
      sleep(1);
      return -1;
   }
}
bool enterPassword(User user){
   int wrong = 0;
   char password[16];
enterPassword:
   cout << "Enter Passsword : ";
   cin >> password;
   if (strcmp(password, user.getPassword()) == 0) {
      cout << "Login Success . . ." << endl;
      return true;
   } else {
      wrong += 1;
      cout << "Incorect Password" << endl;
      sleep(1);
      if (wrong >= 3) {
         cout << "Incorect Password to many time" << endl;
         sleep(1);
         return false;
      }
      goto enterPassword;
   }
}