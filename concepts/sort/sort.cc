#include <algorithm>
#include <list>
#include <concepts>

int main() {
  std::list my_list{1, 10, 5, 2, 4};
  std::sort(my_list.begin(), my_list.end());
}
