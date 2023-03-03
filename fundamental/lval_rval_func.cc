#include <iostream>

class Widget {
  public:
  void doWork() && {
    std::cout << "doWork() && triggered" << std::endl;
  }

  void doWork() & {
    std::cout << "doWork() & triggered" << std::endl;
  }
};


Widget && makeWidget() {
  return std::move(Widget());
}

int main() {
  Widget w;
  w.doWork();
  makeWidget().doWork();
}