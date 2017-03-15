

```cpp

#include <iostream>
#include <experimental/optional>
#include <string>
#include <vector>
#include <dlfcn.h>

using std::experimental::optional;
using std::experimental::nullopt;
using std::uintptr_t;
using std::vector;
using std::string;
using std::cout;
using std::cerr;
using std::endl;
using std::function;;


auto dlopenPlus(const string& path) -> optional<uintptr_t> {
  // https://linux.die.net/man/3/dlopen
  void* ptr = dlopen(path.c_str(), RTLD_LAZY);
  if(ptr == nullptr) return nullopt;
  else               return (uintptr_t)ptr;
}

auto dlsymPlus(const uintptr_t libptr, const string& name) -> optional<uintptr_t> {
  void* ptr = dlsym((void*)libptr, name.c_str());
  if(ptr == nullptr) return nullopt;
  else               return (uintptr_t)ptr;
}


using rungekutta_t = double(*)(
                       function<double(double, double)>& f,
                       double a,
                       double b,
                       double y0,
                       int n
                     );

auto f(double x,double y)->double{
  return x*y;
}


auto main(const int argc, const char* const* const argv) -> int {
  // http://vivi.dyndns.org/tech/cpp/vector.html
  const vector<string> args(argv , argv + argc);
  cout <<  "[" << args[0];
  for (int i=1; i < args.size(); i++){ cout << ", " << args[i]; }
  cout << "]" << endl;
  if(args.size() != 2){
    cerr << "need argument" << endl;
    return 1;
  } 
  auto opt_lib = dlopenPlus(args[1]);
  if(!opt_lib){
    cerr << "module not found" << endl;
    return 1;
  }
  const uintptr_t libptr = *opt_lib;
  cout << libptr << endl;
  const optional<uintptr_t> opt_fn = dlsymPlus(libptr, "rungekutta");
  if(!opt_fn){
    cerr << "function not found" << endl;
    return 1;
  }
  const uintptr_t fnptr = *opt_fn;
  cout << fnptr << endl;
  rungekutta_t rungekutta = reinterpret_cast<rungekutta_t>(fnptr);
  
  rungekutta(static_cast<function<double(double, double)>>(f), 0, 0.05, 1, 1000);
  return 0;
}

```
