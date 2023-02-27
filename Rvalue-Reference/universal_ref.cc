#include <iostream>
#include <string>

void test_func(int && x) {}


void test_str(std::string && x) {
  std::cout << "test_str(std::string &&x) is called" << std::endl;
}
void test_str(const std::string &x) {
  std::cout << "test_str(const std::string &x) is called" << std::endl;
}


int main() {
  auto && x = 10;
  // test_func(x);
  int a = 10;
  test_func(std::move(a));
  test_str("Hello World!");
}