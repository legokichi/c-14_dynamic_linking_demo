#include <functional>
using std::function;
#include <vector>
using std::vector;
#include <tuple>
using std::tuple;
#include <list> 
using std::list;

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
#include <algorithm>
using std::for_each;
using std::transform;
using std::sort;
using std::greater;
using std::max_element;
#include <numeric>
using std::accumulate;
#include <cmath>
using std::pow;
#include <iterator>
using std::begin;
using std::end;


auto rungekutta(
                  function<double(double, double)>& f,
                  double a,
                  double b,
                  double y0,
                  int n
                )-> vector<double> {
  vector<double> y(n);
  double h = (b - a)/static_cast<double>(n);
  double x = a;
  y[0] = y0;
  for(int i=0; i<n; i++){
    double s1 = f(x,         y[i]           );
    double s2 = f(x + h/2.0, y[i] + h*s1/2.0);
    double s3 = f(x + h/2.0, y[i] + h*s2/2.0);
    double s4 = f(x + h,     y[i] + h*s3    );
    x = x + h;
    y[i+1] = y[i] + h/6.0*(s1 + 2.0*s2 + 2.0*s3 + s4);
  }
  return y;
}


// Runge–Kutta
auto main()-> int {
    int n = 10;
    double a = 0.0;
    double b = 1.0;
    double y0 = 1.0;
    function<double(double, double)> f = [](double x, double y)->double{ return x + y; };
    vector<double> y = rungekutta(f, a, b, y0, n);
    for_each(begin(y), end(y), [](auto elm){
        cout << elm << endl;
    });
    return 0;
}




