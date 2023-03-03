#include <iostream>
using namespace std;

class A {
    public:
    A() {
        cout << "A is created" << endl;
    }
    ~A() {
        cout << "A is destroyed" << endl;
    }
};
class B {
    public:
    B() {
        cout << "B is created" << endl;
    }
    ~B() {
        cout << "B is destroyed" << endl;
    }
};
class C {
    public:
    C() {
        cout << "C is created" << endl;
    }
    ~C() {
        cout << "C is destroyed" << endl;
    }
};

/**
 * Note it follow the list of inheritance instead of initialization list
*/
class Composed: public A, public B, public C {
    public:
    Composed() {
      std::cout << "Composed is created" << endl;
    }
    ~Composed() {
      std::cout << "Composed is destroyed" << endl;
    }
};

int main() {
    Composed c;
}