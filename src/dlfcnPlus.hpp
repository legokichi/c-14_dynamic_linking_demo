#include <experimental/optional>
#include <dlfcn.h>

using std::experimental::optional;
using std::experimental::nullopt;
using std::uintptr_t;
using std::string;

auto dlopenPlus(const string& path) -> optional<uintptr_t> {
  // https://linux.die.net/man/3/dlopen
  void* ptr = dlopen(path.c_str(), RTLD_LAZY);
  if(ptr == nullptr) return nullopt;
  else         return (uintptr_t)ptr;
}

auto dlsymPlus(const uintptr_t libptr, const string& name) -> optional<uintptr_t> {
  void* ptr = dlsym((void*)libptr, name.c_str());
  if(ptr == nullptr) return nullopt;
  else         return (uintptr_t)ptr;
}
