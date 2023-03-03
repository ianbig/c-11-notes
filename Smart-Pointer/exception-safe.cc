#include <iostream>
#include <memory>

class Widget {};

int computePriority() {
  // do some ops
  std::cout << "computePriority called" << std::endl;
  throw std::exception();
  return 1;
}

void processWidget(std::shared_ptr<Widget> ptr, int priority) {
  // do some ops
  std::cout << "ProcessWidget called" << std::endl; // not reached
}

int main() {
  try {
    processWidget(std::make_shared<Widget>(), computePriority());
  } catch (std::exception & e) {
    
  }
}