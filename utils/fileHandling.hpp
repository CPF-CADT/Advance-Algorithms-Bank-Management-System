#ifndef CRUDE_BINARY
#define CRUDE_BINARY
#include <fstream>
#include"../utils/arrayList.hpp"
#include "../utils/LinkList.hpp"
#include <iomanip>
#include <cassert>
#include <cstdio>
#include <fstream>
#include <vector>

// template <typename Object> void writeToBinary(const string& filename, const vector<Object>& array) {
//    ofstream file(filename, ios::binary);
//    if (file) {
//          int length = array.size();
//          file.write((char *)(&length), sizeof(length));
//          file.write((char *)(array.data()), sizeof(Object) * length); 
//          file.close();
//    }else{
//       throw runtime_error("Cannot open file");
//    }
// }

// template <typename Object> void readFromBinary(const string& filename, vector<Object>& array) {
//    ifstream file(filename, ios::binary);
//    if (file) {
//       int length;
//       if(file.read((char *)(&length), sizeof(length)));
//       array.resize(length); // set size for vector et get new value if dont set it will error because vector have more that last size
//       file.read((char *)(array.data()), sizeof(Object) * length); 
//       file.close();
//    } else {
//       throw runtime_error("Cannot open file");
//    }
// }
template <typename Object> void writeToBinary(const string& filename, ArrayList<Object> &array) {
   remove(filename.c_str()); 
   for(int i=0;i<array.getLength();i++){
      array.getValue(i).writeToFile(filename);
   }
}

template <typename Object> bool readFromBinary(const string& filename, ArrayList<Object> &array) {
   ifstream readFile(filename, ios::binary);
   Object tempUser;
   array.clear();
   while(readFile.peek() != EOF){
      tempUser.readFileBin(readFile);
      array.push(tempUser);
   }
   readFile.close();
   return true;
}
void writeString(ofstream &writeFile, string &str){
   size_t sizeStr = str.size();
   writeFile.write((char *)(&sizeStr), sizeof(sizeStr));
   writeFile.write(str.c_str(), sizeStr);
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
// template <typename Object> void writeArrayList(ofstream &writeFile, ArrayList<Object> &list){
//    int lengthList = list.getLength();
//    writeFile.write((char *)(&lengthList), sizeof(lengthList));
//    for(int i=0;i<lengthList;i++){
//       Object value = list.getValue(i);
//       writeFile.write((char *)(&value), sizeof(Object));
//    }
// }
// template <typename Object> void readArrayList(ifstream &readFile,ArrayList<Object> list){
//    int lengthList;
//    Object value;
//    readFile.read((char *)(&lengthList), sizeof(lengthList));
//    list.setSize(lengthList);
//    for(int i=0;i<lengthList;i++){
//       readFile.read((char *)(&value), sizeof(Object));
//       list.push(value);
//    }
// }

template <typename Object> void writeArrayList(ofstream &writeFile, vector<Object> &list){
   size_t lengthList = list.size();
   writeFile.write((char *)(&lengthList), sizeof(lengthList));
   writeFile.write((char *)(list.data()), sizeof(Object) * lengthList);
}
template <typename Object> void readArrayList(ifstream &readFile,vector<Object> &list){
   size_t lengthList;
   readFile.read((char *)(&lengthList), sizeof(lengthList));
   list.resize(lengthList);
   readFile.read((char *)(list.data()), sizeof(Object) * lengthList);
}
#endif