#include "header.h"

class Priority_Queue{
    fibonacciHeap f;
    public : 
      void insert(int key, int value){
          f.insert(key, value);
      }

      Node* find(int value){
            return f.find(f.H, value);
        }

      Node* Extract_Max(){
          return f.Extract_Max();
        }

      Node* find_max(){
          return f.find_max();
        }

      Node* meld(Priority_Queue f1){
          f.meld(f1.f);
      }

      bool is_empty(){
          return f.is_empty();
      } 

      void print(){
          f.print();
      }

      void increase_key(int key, int value){
          f.increase_key(key, value);
      }

      void delete_key(int key){
          f.delete_key(key);
      } 


};

