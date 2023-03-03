#include <string>
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
class Composed {
    public:
    A a;
    B b;
    C c;
    Composed() {}
    ~Composed() {}
};

int main() {
    Composed c;
}