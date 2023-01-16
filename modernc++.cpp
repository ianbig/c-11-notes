#include <iostream>
#include <list>
#include <vector>
#include <exception>
#include <utility>

class Widget {
  private:
    int x{1};
    int y{2};
    // int z(3); compile error
  public:
    Widget() {
      std::cout << "default construtor called" << std::endl;
    }

    Widget(int a, int b) {
      std::cout << "Widget(int a, int b) is called" << std::endl;
    }

    Widget(std::initializer_list<double> x) {
      std::cout << "Widget(std::initializer_list<double> x) is called" << std::endl; 
    }
};

void f(int x) {
  std::cout << "f(int x) is called" << std::endl;
}

void f(void * x) {
  std::cout << "f(void * x) is called" << std::endl;
}

template<typename T>
using typelist = std::list<T, std::vector<T>>;

// the same as
template<typename T>
struct mytypelist {
  typedef std::list<T, std::vector<T>> typelist;
};

template <typename T>
class AliasTestClass {
  typename mytypelist<T>::typelist typedef_declare;
  typelist<T> alias_declare;
};

class DelClass {
  public:
    void unwanted_func() = delete;
};

class OverrideBase {
  public:
    virtual void f() {}
};

class OverrideClass : OverrideBase {
  public:
  virtual void f() override {}
};

template <typename C, typename V>
void find_and_insert(C container, V search_val, V insert_val) {
  using std::begin;
  using std::end;

  auto it = std::find(begin(container), end(container), search_val);
  container.insert(it, insert_val);
}

void func_throw_excp_98() throw() {

}

void func_throw_excp() noexcept {
} // optimized than throw version

void swap(Widget & w1, Widget & w2) noexcept {}

template <typename T, typename U>
void swap(std::pair<T, U> p1, std::pair<T, U> p2) noexcept(noexcept(swap(p1.first, p2.first) && noexcept(p1.second, p2.second))) {}

constexpr int get_huge_sz() {
  return 1000;
}

class Polynomial {
  mutable bool rootsValid{false};
  mutable int rootVals{-1};
  public:
    int root() const {
      if (!rootsValid) {
        rootsValid = true;
        rootVals = 10;
      }

      return rootVals;
    }
};

class Base {
  public:
  Base() {
    std::cout << "Base is called" << std::endl;
  }

  virtual ~Base() {
    std::cout << "~Base is called" << std::endl;
  }
};

class Derived : public Base {
  public:
  Derived() {
    std::cout << "Derived is called" << std::endl;
  }

  virtual ~Derived() {
    std::cout << "~Derived is called" << std::endl;
  }
};


int main() {
  /**
   * Item 7: use brace initialization
  */
  int a, b, c;
  // double a, b, c; not prohbitted implicit narrowing conversions among built-in types
  int x{a + b +c};

  // Widget w(); this would be intepreted as a function, solution as below
  Widget w{};
  // the brace initializer could be used in anywhere like atomic type, class member function initialization
  // however, initializer list and overloading would truely mess up brace initialization
  Widget w2{1, 2}; // this would call Widget(std::initializer_list<double> x) instead of Widget(int a, int b) even its a better choice
  Widget w3{};
  Widget w4({});

  /** 
   * To sum up, there is no better way of choosing between brace {} and paranthesis (), just choose one, and do it consistently, and understand its pros and cons
   * For brace initalization, it has the advantage of
   *  1. it could be use nearly everywhere: atomic type, class initialization
   *  2, it could avoid most vexing parse
   * 
   * For its cons, is the intialization list overshawding all the potential matching overloading function
   * 
   * For paranthesis, it is basically the flip of brace initialization
   */

  // f(NULL); lead to compile error

  /**
   * Item 8: use nullptr over NULL, 0
  */

  /**
   * Item 9: prefer using aliasing over typedef, see the above mytypelist and typelise for more understanding
  */

  /**
   * Item 10: prefer scoped enum class to unscoped enum
   *  1. strong typed
   *  2. avoid namespace pollution
  */
  enum class Color { black, white, red };
  // Color cw = black;
  Color cw = Color::black;

  /**
   * Item 11: use deleted over private undefined function
   * There are times developer want to forbit function (such as copy constructor) for client code to use
  */

  /**
   * Item 12: use override for derived classs, since a lot of small missing could lead to derived class
   * not really override base class. Rules for override class
   * The base class function must be virtual.
   * The base and derived function names must be identical (except in the case of destructors).
   * The parameter types of the base and derived functions must be identical.
   * The constness of the base and derived functions must be identical.
   * The return types and exception specifications of the base and derived functions must be compatible.
   * The functions’ reference qualifiers must be identical. 
  */

  /**
   * Item 13: prefer constant_iterator over iterator for read-only operation
  */
  std::vector<int> vec;
  find_and_insert<std::vector<int>, int>(vec, 1998, 1983);

  /**
   * Item 14: use noexcept when there is no exception emit
   * Advantages:
   *  1. compiler generate more optimized code (something relate to the unwinding of function stack when exception occur)
   *  2. good interface design (let client code know this function would never emit exception)
   * 
   * However, be really careful when declaring as noexcept, the following is the convention of c++11 to use noexcept
   * By default, all memory deallocation functions and all destructors—both user-defined and compiler-generated—are implicitly noexcept. 
   * There’s thus no need to declare them noexcept
   * 
   * By not careful enough, you would encouter
   *  1. hard to test narrow contract code when pre-condition is failed
   *  2. make the code to clustered and complicated just to maintain the noecept
   *  3. change of noexcept would break client's code depend on it
  */

  /**
   * Item 15: use constexpr whenever possible
   * constexpr object is a constant compile-time known value
   * constexpr object is a constant compile-time known value if all its argument is compile-time known value
   * otherwise its a runtime known value
   * 
   * some advantage would be peformance improvement, if an large array size need to be computed through power function
   * it would be great we could allocate the size for the large array at compile time rather than run-time since dynamic allocation would involve system call
   * which involve trap handling, and imagaine we have multiple large array allocation, if all done in compile time, what a performace boost we could get
  */

  constexpr int sz = 10;
  int myarr[get_huge_sz()] = {0};

  Base * ptr = new Derived();
  delete ptr;

  /**
   * Item 17: know the compiler generate code (esp move contructor, move assignment operator)
   * move operation are only generated by compiler if
   * No copy operations are declared in the class.
   * No move operations are declared in the class.
   * No destructor is declared in the class.
   * 
   * The copy constructor is generated only for classes lacking an explicitly declared copy constructor, 
   * and it’s deleted if a move operation is declared. 
   * 
   * The copy assignment operator is generated only for classes lacking an explicitly declared copy assignment operator, 
   * and it’s deleted if a move operation is declared.
  */

}