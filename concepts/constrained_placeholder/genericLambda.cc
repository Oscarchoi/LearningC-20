#include <iostream>

auto addLambda = [](auto a, auto b) { return a + b; };

int main() {
  std::cout << "addLambda(3, 5) = " << addLambda(3, 5) << std::endl;
}
