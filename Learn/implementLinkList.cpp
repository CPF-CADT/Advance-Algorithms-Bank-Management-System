//nice
#include<iostream>
// #include "../utils/Stu.hpp"
#include "../utils/arrayList.hpp"
#include "../utils/fileHandling.hpp"
#include "../utils/LinkList.hpp"

// class Stu{
// private:
//    char id[100];
// public:
   
// };
int main(){
   LinkList<int> code;
   code.push(10);
   code.push(30);
   cout<<code.getValue(1)<<endl;
   cout<<code.getValue(0)<<endl;
   cout<<code.indexOf(10)<<endl;
   return 0;
}