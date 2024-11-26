#include<iostream>
#include<vector>
using namespace std;
template <typename T>
void printArray(T *number,int n){
   for(int i=0;i<n;i++){
      if(i==n-1){
         cout<<number[i]<<".";
      }else{
         cout<<number[i]<<", ";
      }
   }
   cout<<endl;
}
template <typename Type>
void insertionSort(vector<Type> &array){
   for(int i=1;i<array.size();i++){
      int numCompare=array.at(i);
      int j=i-1;
      while(j>=0 && numCompare<array.at(j)){
         array.at(j+1)=array.at(j);
         j--;
      } 
   }
}

template <typename N>
void Swap(N &x,N&y){
   N temp;
   temp=x;
   x=y;
   y=temp;
}
template <typename Type>
void bubbleSort(vector<Type> &array){
   for(int i=0;i<array.size()-1;i++){
      for(int j=0;j<array.size()-i-1;j++){
         if(array.at(j)>array.at(j+1)){
            Swap(array.at(j),array.at(j+1));
         }
      }
   }
}
template <typename Selection>
void selectionSort(vector<Selection> &array){
   int minIndex;
   Selection minValue;
   for(int i=0;i<array.size();i++){
      minIndex=i;
      minValue=array.at(i);
      for(int j=i+1;j<array.size();j++){
         if(minValue>array.at(j)){
            minValue=array.at(j);
            minIndex=j;
         }
      }
      array.at(minIndex)=array.at(i);
      array.at(i)=minValue;
   }
}
template <typename Array>
bool isSorted(vector<Array> &array){
   int direction=0;
   int current=0;
   if(array.empty()) return true;
   for(int i=0;i<array.size()-1;i++){
      if(array.at(i)>array.at(i+1))
         current=-1;
      else if(array.at(i)<array.at(i+1))
         current=1;
      if(i==0 || direction==0) direction=current;
      if(direction!=current && (direction!=0 && current!=0)) //check current is change or not
         return false;
   }
   return true;
}
template <typename T>
int binarySearch(vector<T> &array,T dataToSearch){
   int lowIndex=0,mid;
   int highIndex=array.size()-1;
   while(lowIndex<=highIndex){
      mid=lowIndex+(highIndex-lowIndex)/2;
      if(dataToSearch==array.at(mid)){
         return mid;
      }else if(dataToSearch>array.at(mid)){
         lowIndex=(mid+1);
      }else{
         highIndex=mid-1;
      }
   }
   return -1;
}