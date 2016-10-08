#include <iostream>
#include <vector>
#include "dlfcnPlus.hpp"

using std::experimental::optional;
using std::experimental::nullopt;
using std::uintptr_t;
using std::vector;
using std::string;
using std::cout;
using std::endl;

typedef void (*hello_t)();

auto main(const int argc, const char* const* const argv) -> int {
  // http://vivi.dyndns.org/tech/cpp/vector.html
  const vector<string> args(argv , argv + argc);
  cout <<  "[" << args[0];
  for (int i=1; i < args.size(); i++){ cout << ", " << args[i]; }
  cout << "]" << endl;
  auto opt_lib = dlopenPlus(args[1]);
  if(!opt_lib){
    cout << "module not found" << endl;
    cout << "$ ./bin/a.out ./bin/libhello.so" << endl;
    return 1;
  }
  const uintptr_t libptr = *opt_lib;
  cout << libptr << endl;
  const optional<uintptr_t> opt_fn = dlsymPlus(libptr, "hello");
  if(!opt_fn){
    cout << "function not found" << endl;
    return 1;
  }
  const uintptr_t fnptr = *opt_fn;
  cout << fnptr << endl;
  hello_t hello = (hello_t)fnptr;
  hello();
  return 0;
}
