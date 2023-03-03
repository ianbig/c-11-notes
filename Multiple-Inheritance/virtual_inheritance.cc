#include <iostream>
#include <string>
using namespace std;

void print_create(string name) {
  cout << name << " is created!" << endl; 
}

void print_destroyed(string name) {
  cout << name << " is destroyed" << endl;
}

class A {
  public:
  A() {
    print_create("A");
  }
  ~A() {
    print_destroyed("A");
  }
};
class B {
  public:
  B() {
    print_create("B");
  }
  ~B() {
    print_destroyed("B");
  }
};
class C: public virtual A {
  public:
  C() {
    print_create("C");
  }
  ~C() {
    print_destroyed("C");
  }
};
class D: public virtual A, public virtual B {
  public:
  D() {
    print_create("D");
  }
  ~D() {
    print_destroyed("D");
  }
};
class E: public virtual B {
  public:
  E() {
    print_create("E");
  }
  ~E() {
    print_destroyed("E");
  }
};
class F: public C {
  public:
  F() {
    print_create("F");
  }
  ~F() {
    print_destroyed("F");
  }
};
class G: public virtual C, public virtual D {
  public:
  G() {
    print_create("G");
  }
  ~G() {
    print_destroyed("G");
  }
};
class H: public virtual D, public virtual E {
  public:
  H() {
    print_create("H");
  }
  ~H() {
    print_destroyed("H");
  }
};
class I: public F, public G, public virtual H {
  public:
  I() {
    print_create("I");
  }
  ~I() {
    print_destroyed("I");
  }
};


int main() {
  I i;
}