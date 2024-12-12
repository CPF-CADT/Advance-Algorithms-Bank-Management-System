#ifndef ARRAY_LIST
#define ARRAY_LIST
#include<iostream>
#include<exception>
#include<string>
#include <fstream>
using namespace std;
template<typename Object>
class ArrayList{
private:
   Object *data;
   int length;
public:
   ArrayList(){
      data = new Object[0];
      length=0;
   }
   //destructor -> free memoty space
   ~ArrayList(){
      delete[] data;
      data = nullptr;
   }
   void clear() {
      delete[] data; 
      data = new Object[0]; 
      length = 0;    
   }
   void validateIndex(int index){
      if(index<0 ||index>=length){
         throw runtime_error("Index out of bound");
      }
   }
   // void push(Object value){
   //    data[length] = value;
   //    length+=1;
   // }
   void push(Object value) {
      Object* newData = new Object[length + 1]; 
      for (int i = 0; i < length; i++) {
         newData[i] = data[i]; 
      }
      newData[length] = value; 
      delete[] data;           
      data = newData;          
      length += 1;             
   }
   
   int getLength(){
      return length;
   }
   Object& getValue(int index){
      validateIndex(index);
      return data[index];
   }
   Object *pointerOfAtray(){
      return this->data;
   }
   void setSize(int newLength) {
      Object* newData = new Object[newLength];
      delete[] data;
      data = newData;
      length = newLength;
   }
   void reSize(int newLength) {
      Object* newData = new Object[newLength];
      for (int i = 0; i < length && i < newLength; i++) {
         newData[i] = data[i]; 
      }
      delete[] data;
      data = newData;
      length = newLength; 
   }
   void insertAt(int index,Object value){
      validateIndex(index);
      reSize(length+1);
      for (int i=length-1;i>index;i--) {
         data[i]=data[i-1];
      }
      data[index]=value;
   }
   void removeAt(int index){
      validateIndex(index);
      for(int i=index ;i<length;i++){
         data[i]=data[i+1];
      }
      length--; 
   }
   void updateAt(int index,Object value){
      data[index] = value;
   }
   void increaseLength(){
      length++;
   }
   // writeList(ofstream &writeFile, ArrayList<Object> &list){

   // }
};
#endif