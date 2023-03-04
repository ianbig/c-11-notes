#include <iostream>
#include <memory>

class B;
class A {
  std::shared_ptr<B> b;
  public:
  A() {

  }

  void point(std::shared_ptr<B> b) {

  }
};
class B {
  std::shared_ptr<A> a;
  public:
  B(std::shared_ptr<A> _a) : a(_a) {

  }
};

int main() {
  std::shared_ptr<A> a (new A());
  {
    std::shared_ptr<B> b(new B(a));
    a->point(b);
  }
}