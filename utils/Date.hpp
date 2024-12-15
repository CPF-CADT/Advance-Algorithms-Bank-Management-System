#ifndef CLASS_DATE
#define CLASS_DATE
#include <string>
#include <iostream>
#include <ctime>
#include<exception>
using namespace std;
class Date{
public:
   int day;
   int month;
   int year;
   char nameOfMonth[12][4] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
   Date(){
      day=0;
      month=0;
      year=0;
   }
   bool checkInvalidDate(int day,int month,int year){ 
      bool check=false;
      time_t now = time(0);
      tm *localTime = localtime(&now);
      int currentDay = localTime->tm_mday;
      int currentMonth = localTime->tm_mon + 1;
      int currentYear = 1900 + localTime->tm_year;   
      int daysInMonth[12]={31,28,31,30,31,30,31,31,30,31,30,31};
      // if(year<=currentYear) check = true; //check valid date is grater that now or not
      if((year%4==0&&year%100!=0) || year%400==0) daysInMonth[1]=29;
      if(year>currentYear){
         if(month>=1 && month<=12){
            if(day>=1 && day<=daysInMonth[month-1]){
               check = true;
            }else{
               throw runtime_error("Day is invalid");
               return false;
            } 
         }else{
            throw runtime_error("Month must (1 -12)");
            return false;
         } 
      }else{
         throw runtime_error("Year must in the present");
         return false;
      }
      if(year == (currentYear)) 
         if(month < currentMonth ) {
            throw runtime_error("Month must in future");
            return false;
         }
      return check;
   }
   void setCurrentDate(){
      time_t now = time(0);
      tm *localTime = localtime(&now);
      day = localTime->tm_mday;
      month = localTime->tm_mon + 1;
      year = 1900 + localTime->tm_year; 
   }
   void inputDate(){
      inputDate:
      cout<<"Enter Date"<<endl;
      cout<<"Day    : ";cin>>day;
      cout<<"Month  : ";cin>>month;
      cout<<"year   : ";cin>>year;
      try{
         checkInvalidDate(day,month,year);
      }catch(exception &e){
         cerr<<e.what()<<endl;
         cerr<<"Enter Date Again"<<endl;
         goto inputDate;
      }
   }
   string getDate(){
      return to_string(day)+ " / " + nameOfMonth[month-1] + " / " +to_string(year);
   }
   void nextManyMonth(int nOfMonth){
      setCurrentDate();
      this->month +=nOfMonth;
      while(month>=12){
         month-=12;
         year+=1;
      }
   }
};
#endif