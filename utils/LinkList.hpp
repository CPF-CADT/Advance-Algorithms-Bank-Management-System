#ifndef LINK_LIST
#define LINK_LIST
#include<iostream>
#include<string>
using namespace std;
template<typename ObjectNode>
class Node{
public:
   ObjectNode data;
   Node* next;
   Node(ObjectNode data){
      this->data=data;
      next=nullptr;
   }
};
template<typename Object>
class LinkList{
private:
   Node<Object> *head;
   int length;
public:
   LinkList(){
      head=nullptr;
      length = 0;
   }
   ~LinkList(){
      Node<Object> *current=head;
      while(current){
         Node<Object>* temp=current->next;
         delete current;
         current=temp;
      }
      head=nullptr;
   }
   void validateIndex(int index){
      if(index<0 ||index>=length){
         throw runtime_error("Index out of bound");
      }
   }
   void push(Object data){
      Node<Object> *newNode= new Node<Object>(data);
      if(head==nullptr){
         head=newNode;
      }else{
         Node<Object>* current=head;
         while(current->next){ // while next equal to null pointer loop will stop and next curent  will take the new node
            current=current->next;
         }
         current->next=newNode;
      }
      length++;
   }
   
   Object& getValue(int index){
      validateIndex(index);
      Node<Object> *current=head;
      for(int i=0;i<index;i++){
         current=current->next;
      }
      return current->data;
   }
   int getLength(){
      return length;
   }
   void setSize(int length){
      delete head;
      this->length=length;
   }
   Node<Object>* pointerOfNode(){
      return head;
   }
   void insertAt(int index,Object data){
      validateIndex(index);
      Node<Object> *newNode= new Node<Object>(data);
      Node<Object> *current=head;
      if(index==0){
         head=newNode;
         newNode->next=current;
      }else{
         for(int i=0;i<index;i++){
            current=current->next;
         }
         newNode->next=current->next;
         current->next=newNode;
      }
      length++;
   }
   void removeAt(int index){
      validateIndex(index);
      Node<Object> *current=head;
      if(index==0){
         head=current->next;
      }else{
         Node<Object>* previousNode=nullptr;
         for(int i=0;i<index;i++){
            previousNode=current;
            current=current->next;
         }
         if(current->next==nullptr){
            previousNode=nullptr;
         }else{
            previousNode->next=current->next;
         }
         delete current;
      }
      length--;
   }
   void change(int index,Object newData){
      validateIndex(index);
      Node<Object> *current=head;
      for(int i=0;i<index;i++){
         current=current->next;
      }
      current->data=newData;
   }
   int indexOf(Object data){
      Node<Object> *current=head;
      for(int i=0;i<length;i++){
         if(current->data==data){
            return i;
         }
         current=current->next;
      }
      return -1;
   }
   // void BubleSort(){
   //    Node *loopNode=head;
   //    Node *current=head;
   //    for(int i=0;i<length;i++){
   //       Node* previousNode=nullptr;
   //       for(int j=0;j<length-1-i;j++){
   //          if(current->data>loopNode->data){
   //             current=loopNode;
   //          }
   //          loopNode=loopNode->next;
   //          previousNode=loopNode;
   //       }
   //       current=current->next;
   //    }
   // }
};
#endif