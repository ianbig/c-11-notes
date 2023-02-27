#include <iostream>

class Widget {
  public:
  ~Widget() {}
  Widget & operator=(Widget && rhs) = default;
};

int main() {
  Widget w;
  Widget w2 = w; // it's deleted since there is a move operation defined
}