#include <iostream>
using namespace std;


void func(int * a) {
  cout << "func(int *) is called" << endl;
}

void func(int a) {
  cout << "func(int) is called" << endl;
}

int main() {
  func(0);
  // func(NULL); this would lead to compiler error: call to 'func' is ambiguous
  func(nullptr);
}
