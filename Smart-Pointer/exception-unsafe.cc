#include <iostream>
#include <memory>

class Widget {};

int computePriority() {
  // do some ops
  throw std::exception();
  return 1;
}

void processWidget(std::shared_ptr<Widget> ptr, int priority) {

}

int main() {
  try {
    processWidget(std::shared_ptr<Widget>(new Widget()), computePriority());
  } catch (std::exception & e) {
    
  }
}