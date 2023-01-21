#include <iostream>
#include <string>
#include <vector>
#include <array>

class Widget {
  public:
  std::string name;
  // template<typename T>
  // Widget(T && args) {
  //   std::cout << "Widget forward constructor is called" << std::endl;
  // } 
  // this would overshadow copy constructor, a solution would be enable this when the type T is not Widget

  // template<
  //   typename T,
  //   typename = typename std::enable_if<
  //     !std::is_same<Widget, typename std::decay<T>::type>::value
  //   >::type
  // >
  // Widget(T && args) {
  //   std::cout << "Widget templatized constructor is called" << std::endl;
  // }
  // but this do not solved the inheritance probelm, since the passed in AwesomeWidget is not the same type as Widget

  template<
    typename T,
    typename = typename std::enable_if<
      !std::is_base_of<Widget, typename std::decay<T>::type>::value
    >::type
  >
  Widget(T && args) {
    std::cout << "Widget templatized constructor is called" << std::endl;
  }
  
  Widget() {
    std::cout << "Widget Default Constructor is called" << std::endl;
  }
  Widget(Widget && rhs) {
    std::cout << "move constructor is called" << std::endl;
  }

  Widget(const Widget & rhs) {
    name = rhs.name;
    std::cout << "Widget Copy constructor is called" << rhs.name << std::endl;
  }

  Widget(std::string _name) {
    name = _name;
    std::cout << "Widget(std::string name) is called" << std::endl;
  }

  virtual ~Widget() {
    std::cout << "~Widget is called" << std::endl;
  }

  Widget& operator=(const Widget & rhs) {
    std::cout << "Copy assignment is called" << std::endl;
    return *this;
  }

  Widget & operator=(Widget && rhs) {
    std::cout << "Move assignment is called" << std::endl;
    return *this;
  }

  void set_name(std::string && _name) {
    std::cout << "rval setname is called" << std::endl;
  }

  void set_name(std::string & _name) {
    std::cout << "lval setname is called" << std::endl;
  }
};

class AwesomeWidget : public Widget {
  public:
  std::string supername;

  AwesomeWidget(const AwesomeWidget & rhs) : Widget(rhs) {
    supername = rhs.supername;
    std::cout << "AwesomeWidget Copy cons is called" << std::endl;
  }

  AwesomeWidget() {
    std::cout << "AwesomeWidget default constructor is called" << std::endl;
  }

  AwesomeWidget(std::string name, std::string base) : Widget(base) {
    supername = name;
    std::cout << "AwesomeWidget(std::string name, std::string base) is called" << std::endl;
  }
  ~AwesomeWidget() {
    std::cout << "~AwesomeWidget is called" << std::endl;
  }
};

void r_func(int && r) {
  std::cout << &r << std::endl;
}

/**
 * Similar implemetation of std::move
 * move is just a cast, it do not move anything
 * 
 * Item 23: std::move and std::forward
 * 
 * std::move is an unconditional cast to rvalue
 * std::forward cast to rvalue based on its lvaluness and rvaluness when initialized
 * both do nothing at run-time
*/
// template<typename T>                       // in namespace std
// typename std::remove_reference<T>::type&&
// move(T&& param)
// {
//   using ReturnType =                       // alias declaration;
//     typename remove_reference<T>::type&&;  // see Item 9

//   return static_cast<ReturnType>(param);
// }

/**
 * This explain why we need std::forward
*/

void process(const Widget& lvalArg) {
  std::cout << "lvalue process is called" << std::endl;
}     // process lvalues
void process(Widget&& rvalArg) {
  std::cout << "rvalue process is called" << std::endl;
}    // process rvalues

template<typename T>                     // template that passes
void logAndProcess(T&& param)            // param is a universal reference
{
  process(std::forward<T>(param)); // since param is an lvalue, we need to cast it to rvalue
}

Widget makeWidget() {
  Widget w;
  return w; // this is good since it applied the RVO (the compiler would generate a memory (not destroyed even function is out of scope) 
  // for the local object, and hence exclude the copy or move operation)
}

Widget makeWidget_do_not_write_version() {
  Widget w;
  return std::move(w); // this preclude the RVO
}

template<typename T>
void set_widget(T && args) {
  T localObjv(std::forward<T>(args));
}

/**
 * Good time to return std::move or std::forward
*/
Widget return_param(Widget && widget) {
  return std::move(widget); // this avoid extra copying
}

std::vector<std::string> names;

/**
 * Do not write overloading on universal reference
*/
template<typename T>
void log_name(T && name) {
  std::cout << "invoke template function" << std::endl;
  names.emplace_back(name);
}

// but if you write this
void log_name(int idx) {
  std::cout << "invoke int function" << std::endl;
  std::string name = names[idx];
  names.emplace_back(name);
}

// Below are solution to universal reference that need overloaded functionality
// this is called tag dispatch
template<typename T>
void log_name_correct_impl(T && name, std::false_type) {
  std::cout << "non-integral version is called" << std::endl;
}

template<typename T>
void log_name_correct_impl(T && idx, std::true_type) {
  // std::string name = names[idx];
  // log_name_correct(name);
  std::cout << "integral version is called" << std::endl;
}

template<typename T>
void log_name_correct(T && name) {
  log_name_correct_impl(
    std::forward<T>(name),
    std::is_integral<typename std::remove_reference<T>::type>()
  );
}

/**
 * Below code explain why std::forward could distinguish between lval and rval of params
*/
template<typename T>
T&& forward(typename std::remove_reference<T>::type & param) {
  return static_cast<T&&>(param);
}

// In the above code if you passed in a lval Widget, T is deduced to Widget&
// if passed in rval, T is deduced to Widget
void f(int a, int b) {
  std::cout << "reach f, a is " << a << ", and b is " << b << std::endl;
}

template<typename ...Ts>
void fwd(Ts&&... args) {
  f(std::forward<Ts>(args)...);
}

int main() {
  int && r = 2;
  std::cout << &r << std::endl;
  int lval = 10;
  r_func(2);

  Widget w;
  logAndProcess(w); // trigger lvalue process
  logAndProcess(std::move(w)); // trigger rvalue process

  w.set_name("I am Ian");
  std::string ls("I am Ian");
  w.set_name(ls);

  /**
   * Item 25: use std::move on rvalue reference and std::forward on universal reference (whether its a lvaue or a rvalue operation the std::forward
   * could determined)
   * 
   * never apply std::move or std::forward on local object return since it preclude the Return Value Optimiziation (RVO)
  */
  Widget w2;
  auto w3 = makeWidget();
  set_widget(std::move(w2));
  set_widget(w3);

  /**
   * Do not write overloading on universal reference
  */
  short idx = 0;
  // log_name(idx);

  std::string name = "Ian";
  log_name_correct(name); // should call non-integral version
  log_name_correct(idx); // should call integral version

  // illustration to why we need virtual destructor but not the constructor
  // Widget * wptr = new AwesomeWidget();
  // delete wptr;

  AwesomeWidget aw("Ian", "Awesome");
  AwesomeWidget aw2 = aw;
  std::cout << aw2.supername << aw2.name << std::endl;
  std::cout << aw.supername << aw.name << std::endl;

  int idx = 10;
  Widget aw3(idx);

  /**
   * Item 28: understand reference collapse
   * 
   * four scenario reference collapse would occur
   * 1. template type deduction
   * 2. auto
   * 3. typedef or type alias (i.e. using)
   * 4. decltype 
   * 
   * 
   * see the above example to understand more
  */

  auto && aw_lref = aw3; // since pass in lval, so it expand to (Widget&) && aw_lref = aw3;
  auto && aw_rref = Widget(); // pass in rval, so it expand to (Widget) && aw_rref

  int && a = 10;
  int c = 100;
  c = std::move(a);

  std::cout << c << ", " << a << std::endl;

  /**
   * Item 29: assume move operation are not present, not cheap, not use
   * 
   * not present: some container or type may not support move operation (either standard or self defined)
   * not cheap: like the example below, the operation cost is the same as copy (since it is truely a copy)
   * not use: move only could work if provided move do not throw exception (assume in the scenario where original function is a nothrow)
  */

  std::array<int, 5> arr = {1, 2, 3, 4, 5};
  auto crr = std::move(arr);

  for (auto it = arr.begin(); it != arr.end(); it++) {
    std::cout << *it << ", ";
  }
  std::cout << std::endl;

  for (auto it = crr.begin(); it != crr.end(); it++) {
    std::cout << *it << ", ";
  }
  std::cout << std::endl;

  /**
   * Item 30: when would your perfect forwarding fail
   * 
   * What is perfect forwarding?
   * forwarding mean forward the argument to other function to process, a perfect forwarding reserver the origin of argument
   * that means, it reverse its constness, lvalue reference or rvalue reference
   * 
   * When it would fail if you pass in
   * 1. done it with brace list
   * 2. With NULL or 0 (which you should use nullptr what so ever)
   * 3. overloaded function or template functoin, since it is many function to choose how could compiler know which one to choose
   * 4. passing bitfield
   * 5. Declaration-only integral static const and constexpr data members (not understand what is this)
  */
  fwd(10, 20);
}