#include <iostream>
#include <string>
#include <sstream>
using namespace std;

template<typename T, typename C, T C::*M>
T getMember2(C * us) {
  return (us->*M);
}

struct MyStruct {
  int myInt;
} str;

int main() {
  str.myInt = 5;
  int myInt = getMember2<int, MyStruct, &MyStruct::myInt>(&str);
  cout << " (" << myInt << ")\n";
  return 0;
}
