#include <iostream>
#include <string>
#include <sstream>
using namespace std;

template <typename T>
struct is_pointer_impl {
   static void is() {
     cout<<"no ";
 }
}; 
template <typename T>
struct is_pointer_impl<T*> {
   static void is() {
     cout<<"yes ";
  }
};

 template <typename T> 
   void isPointer() {
     is_pointer_impl<T>::is();
 }


int main() {
  isPointer<int>();
  isPointer<int*>();  
  return 0;
}

