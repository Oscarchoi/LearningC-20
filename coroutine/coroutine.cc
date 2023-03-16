#include <iostream>

int main() {
  auto result = 2 <=> 1;
  std::cout << "Hello world!" << (result > 0) << std::endl;
  return 0;
}
