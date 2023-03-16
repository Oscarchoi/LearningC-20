#include <iostream>
#include <concepts>

template <typename T>
concept Integral = std::is_integral<T>::value;

Integral auto gcd(Integral auto a, Integral auto b) {
	if( b==0 ) return a;
	else return gcd(b, a % b);
}

int main() {
  int a = 15;
  int b = 39;
  std::cout << "gcd(" << a << ", " << b << ") = " << gcd(a, b) << std::endl;
  // gcd(15, 39) = 3
  
  double c = 15.5;
  double d = 39.1;
  // compile error
  // std::cout << "gcd(" << c << ", " << d << ") = " << gcd(c, d) << std::endl;
  
  /* error message
  ./gcd.cc:20:54: error: no matching function for call to 'gcd'
  std::cout << "gcd(" << c << ", " << d << ") = " << gcd(c, d) << std::endl;
                                                     ^~~
  ./gcd.cc:7:15: note: candidate template ignored: constraints not satisfied [with a:auto = double, b:auto = double]
  Integral auto gcd(Integral auto a, Integral auto b) {
              ^
  ./gcd.cc:7:19: note: because 'double' does not satisfy 'Integral'
  Integral auto gcd(Integral auto a, Integral auto b) {
                  ^
  ./gcd.cc:5:20: note: because 'std::is_integral<double>::value' evaluated to false concept Integral = std::is_integral<T>::value;
                   ^
  1 error generated.
  */ 
}
