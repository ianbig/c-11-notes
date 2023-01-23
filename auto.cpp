#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

/**
 * benefit of using auto:
 *  1. prevent uninitialized data
 *  2. less typing
 *  3. more portable
 *  4. less type conversion error (the one in not using auto section of below)
 * 
 * Difference btw closure and lamba expression is like class (lamba expression) to class instance (closure)
*/

std::vector<bool> features() {
  return std::vector<bool>(6, 1);
}

void process(bool priority) {

}

int main() {
  /**
   * the key difference between using std::function and auto (and why auto is better)
   * auto just the as many memory as the closure need; however, the std::function would use more than that (closure itself + the class of std::function)
  */
  std::function<bool (int, int)> fn_function = [](int a, int b) { return a < b; };
  auto fn_auto = [](int a, int b) { return a < b; };

  std::cout << fn_auto(2, 3) << std::endl;;
  std::cout << fn_function(4, 5) << std::endl;

  std::unordered_map<std::string, int> x = {{"a", 98}, {"b", 99}};
  // not using auto 
  for (const std::pair<std::string, int> &p : x) {
    // do something to change p's value, it would create a temporary object of x for p to point to since the type
    // is not matched (i.e. const std::pair<std::string, int> to const std::pair<const std::string, int>)
  }

  for (const auto &p : x) {
    // do something to change p's value, would change the underlying p
  }

  /**
   * Item 6: specify type for the compiler when using auto
  */
  bool high_priority = features()[5];
  process(high_priority);

  auto high_priority_undefined = features()[5]; // this return vector<bool>::reference, which is a proxy class, a class for emulating or augmenting the behavior of some other class (such as unique_ptr)
  process(high_priority); // this is undefined behavior, since this depend on the implementation of vector<bool>::reference, in the book this would cause the dangling behavior pointer
  // the above undefined behavior is often occurred, when programmer try to use auto on invisible proxy class

  // below is a good solution, that "explicit" cast the type
  auto high_priority_undefined = static_cast<bool>(features()[5]);

}