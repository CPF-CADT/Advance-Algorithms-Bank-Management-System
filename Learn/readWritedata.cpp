#include <iostream>
#include <fstream>
#include <string>
#include "../utils/arrayList.hpp"
#include "../utils/fileHandling.hpp"

using namespace std;

class User
{
private:
   int id;
   string name;
   string address;

public:
   User()
   {
      id = 0;
      name = " ";
      address = " ";
   }
   User(int id, string name, string address)
   {
      this->id = id;
      this->name = name;
      this->address = address;
   }
   void input(ofstream &writeFile){
      cout<<"ID : ";cin>>id;
      cout<<"Name : ";cin>>name;
      cout<<"Address :";cin>>address;
      writeToBinary(writeFile);
   }
   void writeString(ofstream &writeFile, string &str){
      size_t sizeStr = str.size();
      writeFile.write((char *)(&sizeStr), sizeof(sizeStr));
      writeFile.write(str.c_str(), sizeStr);
   }
   void writeToBinary(ofstream &writeFile){
      writeFile.write((char *)(&id), sizeof(id));
      writeString(writeFile, name);
      writeString(writeFile, address);
   }
   string readString(ifstream &readFile){
      size_t sizeStr;
      readFile.read((char *)(&sizeStr), sizeof(sizeStr));
      char *tempString = new char[sizeStr + 1];
      readFile.read(tempString, sizeStr);
      tempString[sizeStr] = '\0';
      string str(tempString);
      delete[] tempString;
      return str;
   }
   void readFile(ifstream &readFile){
      readFile.read((char *)(&id), sizeof(id));
      name = readString(readFile);
      address = readString(readFile);
   }
   void display() const
   {
      cout << "ID: " << id << ", Name: " << name << ", Address: " << address << endl;
   }
};
void write(User user[],const string  &filename,int index){
   ofstream writeFile(filename, ios::binary);
   for(int i=0;i<index;i++){
      user[i].writeToBinary(writeFile);
   }
   writeFile.close();
}
void read(User user[],const string  &filename){
   ifstream readFile(filename, ios::binary);
   int i=0;
   while (readFile.peek() != EOF){ 
      user[i].readFromBinary(readFile);
      i++;
   }
   readFile.close();
}
int main()
{
    // Array of User objects
   // ofstream file("userdata.dat", ios::binary);
   ArrayList<User> users;
   // User user;
   // user.input(file);
   // users.push(user);

   // user.input(file);
   // users.push(user);

   cout << "Data written to users.dat successfully." << endl;
   // Reading data from the binary file
   readFromBinary("userdata.dat",users);
   for(int i=0;i<2;i++){
      users.getValue(i).display();
   }
   return 0;
}