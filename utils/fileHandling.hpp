#ifndef CRUDE_BINARY
#define CRUDE_BINARY
#include <fstream>
#include"../utils/arrayList.hpp"
#include "../utils/LinkList.hpp"
#include <cassert>

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
   ofstream file(filename, ios::app |ios::binary);
   if (file) {
         int length = array.getLength();
         file.write((char *)(&length), sizeof(length));
         file.write((char *)(array.pointerOfAtray()), sizeof(Object) * length); 
         file.close();
   }else{
      throw runtime_error("Cannot Write file");
   }
}

template <typename Object> void readFromBinary(const string& filename, ArrayList<Object> &array) {
   ifstream file(filename, std::ios::in | std::ios::binary);
   if (file) {
      int length;
      file.read((char *)(&length), sizeof(length));
      array.setSize(length);
      file.read((char *)(array.pointerOfAtray()), sizeof(Object) * length); 
      file.close();
   } 
   else {
      cerr<<"Cannot Read file"<<endl;
   }
}

#endif