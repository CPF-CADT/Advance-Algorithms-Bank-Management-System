#include<iostream>
#include "../utils/fileHandling.hpp"
using namespace std;
int main(){
   vector<string> name;
   // name.push_back("Nak");
   // name.push_back("Jak");
   // name.push_back("Bob");
   // ofstream writeFile("listStr.dat",ios::binary);
   // writeVectorStr(writeFile,name);
   ifstream readFile("listStr.dat", ios::binary);
   readVectorStr(readFile,name);
   for(auto i:name){
      cout<<i<<endl;
   }
   return 0;
}