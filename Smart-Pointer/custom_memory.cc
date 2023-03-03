#include <iostream>
#include <memory>
#include <cstdlib>

class Widget {
  public:
  void * operator new(size_t size) {
    void * p = malloc(sizeof(Widget));
    return p;
  }

  void operator delete(void * p) {
    free(p);
    p = nullptr;
  }

  void say() {
    std::cout << "hi" << std::endl;
  }
};

int main() {
  auto sp = std::make_shared<Widget>();
  sp.reset();
  auto sp2 = sp;
  sp2->say();
}