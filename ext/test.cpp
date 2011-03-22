#include <iostream>
template <class T>
T do_it(T h) {
  std::cout << "Hello World!" << std::endl;
  return do_it_again(h);
}

template <class T>
T do_it_again(T h) {
  std::cout << "Hello World!" << std::endl;
  return h;
}

int main() {
  std::cout << "Hello World!" << std::endl;
  return do_it<int>(0);
}
