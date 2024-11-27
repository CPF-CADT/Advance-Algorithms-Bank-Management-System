#ifndef CRUDE_BINARY
#define CRUDE_BINARY
#include <fstream>
#include "../utils/User.hpp"
#include"../utils/arrayList.hpp"
template <class Object> void writeToBinary(const string& filename, const vector<Object>& array) {
   ofstream file(filename, ios::binary);
   if (file) {
         int length = array.size();
         file.write((char *)(&length), sizeof(length));
         file.write((char *)(array.array()), sizeof(Object) * length); 
         file.close();
   }else{
      throw runtime_error("Cannot open file");
   }
}

template <class Object> void readFromBinary(const string& filename, vector<Object>& array) {
   ifstream file(filename, ios::binary);
   if (file) {
      int length;
      file.read((char *)(&length), sizeof(length));
      array.resize(length); // set size for vector et get new value if dont set it will error because vector have more that last size
      file.read((char *)(array.array()), sizeof(Object) * length); 
      file.close();
   } else {
      throw runtime_error("Cannot open file");
   }
}

template <class Object> void writeToBinary(const string& filename, ArrayList<Object> &array) {
   ofstream file(filename, ios::binary);
   if (file) {
         int length = array.getLength();
         file.write((char *)(&length), sizeof(length));
         file.write((char *)(array.pointerOfAtray()), sizeof(Object) * length); 
         file.close();
   }else{
      throw runtime_error("Cannot open file");
   }
}

template <class Object> void readFromBinary(const string& filename, ArrayList<Object> &array) {
   ifstream file(filename, ios::binary);
   if (file) {
      int length;
      file.read((char *)(&length), sizeof(length));
      array.setSize(length);
      file.read((char *)(array.pointerOfAtray()), sizeof(Object) * length); 
      file.close();
   } else {
      throw runtime_error("Cannot open file");
   }
}
#endif