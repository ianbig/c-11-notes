#include <iostream>
#include <vector>

template<typename T, std::size_t N>
std::size_t arr_size(T (&) [N]) {
  return N;
}

template <typename Container, typename Index>
auto get(Container & c, Index i) -> decltype(c[i]) {
  return c[i];
}

// template <typename Container, typename Index>
// decltype(auto) get14(Container & c, Index i) {
//     return c[i];
// }

int main() {
  int arr[] = {1, 2, 3};
  std::cout << arr_size(arr) << std::endl;

  std::vector<int> a = {1, 2, 3};
  // decltype
  std::cout << get(a, 1) << std::endl;
  // std::cout << get14(a, 0) << std::endl;


  int c = 0;
  decltype(c) x;
  
  x = 20;
  // x = "I am awesome";
  std::cout << x << std::endl;

  // hover over the code
  auto x = 10;
  auto y = &x;
}