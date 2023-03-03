#include <iostream>
#include <memory>
#include <vector>

int main() {
  using VI = std::vector<int>;
  // auto up = std::make_unique<VI>(10, 20);
  auto listt = {10, 20};
  /* the code is not working, since perfect forwarding fail to forward bace initializer*/
  // auto up = std::make_unique<VI>({10, 20});
  auto up = std::make_unique<VI>(listt);

  for (auto it = up->begin(); it != up->end(); it++) {
    std::cout << *it << std::endl;
  }

  return 0;
}