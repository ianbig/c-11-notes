#include <iostream>

class Widget {
  public:
  Widget(int a, int b) {
    std::cout << "call Widget(int, int)" << std::endl;
  }

  Widget(std::initializer_list<int> lists) {
    for (auto x : lists) {
      std::cout << x << std::endl;
    }
  }
};


int main() {
  Widget w = {1, 2}; // by adding an initialization list, the construction behavior is totally different
  
}