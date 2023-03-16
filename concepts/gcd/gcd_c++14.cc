#include <iostream>
#include <type_traits>

template <typename T>
T gcd(T a, T b) {
  static_assert(std::is_integral<T>::value, "type is not integer");
  if( b == 0 ) return a;
  else return gcd(b, a % b);
}

int main() {
  int a = 15;
  int b = 39;
  std::cout << "gcd(" << a << ", " << b << ") = " << gcd(a, b) << std::endl;

  double c = 15.3;
  double d = 39.1;
  // compile error
  // std::cout << "gcd(" << c << ", " << d << ") = " << gcd(c, d) << std::endl;

  /* error message
  ./gcd_c++14.cc:6:3: error: static_assert failed due to requirement 'std::is_integral<double>::value' "type is not integer"
    static_assert(std::is_integral<T>::value, "type is not integer");
    ^             ~~~~~~~~~~~~~~~~~~~~~~~~~~
  ./gcd_c++14.cc:18:54: note: in instantiation of function template specialization 'gcd<double>' requested here
    std::cout << "gcd(" << c << ", " << d << ") = " << gcd(c, d) << std::endl;
                                                     ^
  ./gcd_c++14.cc:8:24: error: invalid operands to binary expression ('double' and 'double')
    else return gcd(b, a % b);
                     ~ ^ ~
  2 errors generated.
  */
}

