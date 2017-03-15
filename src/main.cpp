#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <optional>
#include <functional>

using std::optional;
using std::nullopt;
using std::uintptr_t;
using std::vector;
using std::string;
using std::cout;
using std::cerr;
using std::endl;
using std::function;

auto f() -> std::tuple<int, string> {
  return std::make_tuple(3, "A");
}
// const char * const * const argv
//       |    | |     | |     + 変数 argv
//       |    | |     | + 変数は定数
//       |    | |     + この変数の内容はポインタ
//       |    | + このポインタが指す値は定数
//       |    + このポインタが指す値はポインタ値
//       + このポインタが指す値のポインタ値型はchar

auto main(const int argc, const char* const* const argv) -> int {
  const auto [a, b] = f();
  cout << a << b << endl;
  return 0;
}
