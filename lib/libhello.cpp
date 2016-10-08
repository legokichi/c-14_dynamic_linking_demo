#include <iostream>

extern "C" auto hello()-> void {
  std::cout << "hello" << std::endl;
}