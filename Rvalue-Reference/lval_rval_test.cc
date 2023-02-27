/**
 * This code test the rvalue and lvalue interation with raval reference and lval reference
*/

#include <iostream>

// the following is an illustration that passed in parameter is lval
void nestedDoStuff(int && rval) {
  std::cout << "nestedDoStuff(int && rval) is called" << std::endl;
}

void nestedDoStuff(int & lval) {
  std::cout << "nestedDoStuff(int & lval) is called" << std::endl;
}

// end here

void doStuff(int && rval) {
  std::cout << "doStuff(int && rval) is called" << std::endl;
  nestedDoStuff(rval);
}

void doStuff(int & lval) {
  std::cout << "doStuff(int & lval) is called" << std::endl;
}

int main() {
  int a = 10;
  doStuff(a); // expect call doStuff(int & rval)
  doStuff(10); // expect call doStuff(int && rval)
}