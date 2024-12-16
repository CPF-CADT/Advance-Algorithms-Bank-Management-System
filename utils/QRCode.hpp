#ifndef QRCODE
#define QRCODE
#include<iostream>
#include<cstdlib>
#include<exception>
#include<cmath>
#include"./arrayList.hpp"
#include"./algorithms.hpp"
#include"./fileHandling.hpp"
#define CODE_DATA "../Data/code.dat"

using namespace std;
class QRCode{
   private:
      int code;
      float amountKHR;
      float amountUSD;
   public:
      QRCode(){
         code = 0;
         amountKHR = 0.0;
         amountUSD = 0.0;
      }
      bool isCodeExits(const string filename ,vector<int> listCode, int newCode){
         for(auto i:listCode){
            if(i == newCode){
               return true;
            }
         }
         return false;
      }
      int randomValue(vector<int> listCode){
         int random =0;
         randomAgain:
         random = 1000 + rand()%1000;   
         //check validation
         if(isCodeExits(CODE_DATA,listCode,random)){
            goto randomAgain;
         }
         return random;
      }
      void cratePaymentCode(){
         //code
         int op;
         vector<int> listCode;
         ifstream readFile(CODE_DATA, ios::binary);
         if(readFile.is_open()){
            readVector(readFile,listCode);
         }
         readFile.close();
         srand((unsigned) time(NULL));
         cout<<"Choose Currency "<<endl;
         cout<<"1 . KHR"<<endl;
         cout<<"2 . USD"<<endl;
         cout<<" Choose : ";cin>>op;
         switch(op){
            case 1:{
               try{
                  cout<<"Amount (KHR) : ";cin>>amountKHR;
                  if(amountKHR<=0){
                     throw runtime_error("Cureency Must greater that 0 .");
                  }
               }catch(exception &e){
                  cerr<<e.what()<<endl;
               }
               
               code = randomValue(listCode); //check is have or not
               ofstream writeFile(CODE_DATA, ios::trunc | ios::binary);
               writeVector(writeFile,listCode);
               writeFile.close();
            break;
            }
            case 2:{
               try{
                  cout<<"Amount (USD) : ";cin>>amountUSD;
                  if(amountUSD<=0){
                     throw runtime_error("Cureency Must greater that 0 .");
                  }
               }catch(exception &e){
                  cerr<<e.what()<<endl;
               }
               code = randomValue(listCode); //check is have or not
               ofstream writeFile(CODE_DATA, ios::trunc | ios::binary);
               writeVector(writeFile,listCode);
               writeFile.close();
            break;
            }
         }

      }
      // void payMoney(User &users){
      //    //code
      //    int tempCode;
      //    cout<<"Enter Code : ";cin>>tempCode;
      //    for()
      //    // implement next time
      // }
      string getCodeData(){
         if(amountKHR!=0){
            return to_string(code)+ " - " +to_string(round(amountKHR))+" R";
         }else{
            return to_string(code)+ " - " +to_string(amountUSD)+" $";
         }
      }
      string getLoanData(){
         if(amountKHR!=0){
            return to_string(round(amountKHR))+" R" + "  | Loan-Code : " + to_string(code);
         }else{
            return to_string(amountUSD)+" $" + "  | Loan-Code : " + to_string(code);
         }
      }
      int getCode() {
         return code;
      }
      void setCode(int c) {
         code = c;
      }
      float getAmountKHR() {
         return amountKHR;
      }
      void setAmountKHR(float amount) {
         amountKHR = amount;
      }
      float getAmountUSD() {
         return amountUSD;
      }
      void setAmountUSD(float amount) {
         amountUSD = amount;
      }
};
#endif