//nice
#include<iostream>
#include"fileHandling.hpp"
#include"../utils/arrayList.hpp"
class Stu{
private:
   int id;
public:
   Stu(){
      id = 0;
   }
   void input(){
      cout<<"ID : ";cin>>id;
   }
   void output(){
      cout<<id<<endl;
   }
};
int main(){
   ArrayList<Stu> stu;
   Stu s;
   // s.input();
   // stu.push(s);
   // s.input();
   // stu.push(s);
   // writeToBinary("test.bin",stu);
   readFromBinary("test.bin",stu);
   for(int i=0;i<stu.getLength();i++){
      s = stu.getValue(i);
      s.output();
   }
   s.input();
   stu.insertAt(0,s);
   s.input();
   stu.updateAt(1,s);
   // s.input();
   // stu.insertAt(1,s);
   for(int i=0;i<stu.getLength();i++){
      s = stu.getValue(i);
      s.output();
   }
   return 0;
}