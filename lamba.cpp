#include <iostream>
#include <vector>


/**
 * Distinguish between lamba, closure, closure class
 * 
 * lamba is a expression
 * clousure is a run-time object of lamba
 * closure class is the class where a closure is being instantiated
*/

using FilterCont = std::vector<std::function<bool(int)>>;
FilterCont filters;

class Widget {
  private:
  int divider;
  public:
  Widget() : divider(100) {}
  void addFilter();
};

void Widget::addFilter() {
  filters.emplace_back(
    [=](int val) { return val % divider; } // Warning:what it acutually capture is this instead of divider, this might lead to the dangling pointer problem if the object is delete
  );
}

template<typename T>
void normalize(T && x) {
  // aussume normalize would do differently based on lvalue or rvalue
}

int main() {
  int a = 10;
  auto lamba_by_ref = [&]() {
    std::cout << a << std::endl;
  };

  lamba_by_ref();
  a = 200;
  lamba_by_ref();

  auto lamba_by_val = [=]() {
    std::cout << a << std::endl;
  };
  lamba_by_val();
  a = 300;
  lamba_by_val();

  Widget w;
  w.addFilter();

  /**
   * Item 32: use init capture to move object into closure
  */
  std::vector<int> vec;
  auto closure = [vec = std::move(vec)]() {
    // the left vec is in the scope of closure
    // the right vec is the same scope as closure (i.e. within the same level of closure)
  };

  // Note: this is a c++14 features, thouogh there is workaround in c++11 (i.e. through std::bind), counsulting the book when you need to use it

  /**
   * Item 33: generic lamba
  */

  auto generic_lamba = [](auto &&... x) {
    return normalize(std::forward<decltype(x)>(x)...);
  }; // this is some c++14 feature
}