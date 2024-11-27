#ifndef ARRAY_LIST
#define ARRAY_LIST
#include<iostream>
#include<exception>
#include<string>
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
   void validateIndex(int index){
      if(index<0 ||index>=length){
         throw runtime_error("Index out of bound");
      }
   }
   void push(Object value){
      this->data[length]=value;
      length+=1;
   }
   int getLength(){
      return length;
   }
   Object getValue(int index){
      validateIndex(index);
      return data[index];
   }
   Object *pointerOfAtray(){
      return this->data;
   }
   void setSize(int length){
      this->length=length;
   }
   void insertAt(int index,Object value){
      validateIndex(index);
      length++;
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
};
#endif