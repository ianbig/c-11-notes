#include <iostream>

class A {
  public:
  int x;
  A() : x(10) {}
  void print() {
    std::cout << "A is printing " << x << std::endl;
  }
};

class B {
  public:
  int x;
  B() : x(10) {
  }

  void print() {
    std::cout << "B is printing " << x << std::endl;
  }
};

class C : public A, public B {};

int main() {
  C c;
  // c.print(); this would confuse the compiler
  c.A::print();
  c.B::print();
}