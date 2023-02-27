#include <iostream>
#include <vector>

int gid = 0;

class Investmest {
  public:
  int id;
  Investmest() {
    id = gid++;
    std::cout << "Investment is called" << std::endl;
  }

  ~Investmest() {
    std::cout << "~Investment is called id " << id << std::endl;
  }

  Investmest(Investmest && rhs) {

  }
};

void makeLog(Investmest * p) {
  // std::cout << "custom destructor is called" << std::endl;
}

class bad_explample_shared_ptr_class;
using bc = bad_explample_shared_ptr_class;

std::vector<std::shared_ptr<bc>> processed_bc;
class bad_explample_shared_ptr_class {
  public:
  bad_explample_shared_ptr_class() {}
  void process() {
    processed_bc.emplace_back(this); // this is bad since it created another control block for same object (sign for triggered undefined behavior)
  }
};

void f() {
  static int fa;
  std::cout << fa++ << std::endl;
}

class A;
class B;

class A {
  public:
  std::shared_ptr<B> ptr;
  ~A() {
    std::cout << "~A is called" << std::endl;
  }
};

class B {
  public:
  std::shared_ptr<A> ptr;
  ~B() {
    std::cout << "~B is called" << std::endl;
  }
};

class sol_shared_ptr_class;
using sc = sol_shared_ptr_class;
std::vector<std::shared_ptr<sc>> processed_sc;

class sol_shared_ptr_class : public std::enable_shared_from_this<sc> {
  public:
  sol_shared_ptr_class() {
    std::cout << "sc constructor is called" << std::endl;
  }
  ~sol_shared_ptr_class() {
    std::cout << "sc destructor is called" << std::endl;
  }
  void process() {
    processed_sc.emplace_back(shared_from_this()); // but this way lead to undefined behavior, since sc much be already pointer by shared_ptr
    std::cout << "end of process" << std::endl;
  }
};

// best solution make constructor private and create factory function to return std::shared_ptr<sc>

int main() {
  /**
   * Item 18: unique_ptr for exclusive ownership
   *  1. it only have move semantic, hence, any copy operation would be prohibit (compile error)
   *  2. Good use scenario: factory function
   *  3. it can be converted to type shared_ptr
   *  4. it could have self-define deleted ptr
   *  5. it should be as big as raw ptr, when it is not should reconsider the design (this usually occur self-defined delete function, it would better to use lamba expression)
  */
  // std::unique_ptr<int> p(new int(10));
  // std::unique_ptr<int> p2(std::move(p));

  // std::cout << *p2 << std::endl;

  // std::unique_ptr<int[]> p_arr(new int[10]);
  // std::cout << p_arr[3] << std::endl;

  // auto customDel = [](Investmest * p) {
  //   makeLog(p);
  //   delete p;
  // };

  // std::unique_ptr<Investmest, decltype(customDel)> iv(new Investmest(), customDel);
  // iv.reset(new Investmest());

  // std::cout << iv->id << std::endl;

  /**
   * Item 19: shared_ptr
   * shared ptr is often twice as big as unique_ptr (the pointer to object, and pointer to control block)
   * never created shared_ptr from raw_ptr
  */

//  std::shared_ptr<Investmest> sp(new Investmest());
//  std::shared_ptr<Investmest> sp2(new Investmest());

//  sp = sp2;

//  std::shared_ptr<Investmest> sp3;
//  sp3 = std::move(sp2);

//  bc bc1;
// //  bc1.process();
//   std::shared_ptr<sc> sc1(new sc());
//   sc1->process();

//   std::cout << "end of code" << std::endl;

//   // custom deleter diff from shared_ptr
//   auto custom_del = [](Investmest * p) {
//     // some custom ops
//     delete p;
//   };
//   std::shared_ptr<Investmest> sp4(new Investmest(), custom_del);

  /**
   * Item 20: weak ptr
   * 1. atomic operation that checks to see if the std::weak_ptr has expired and, if not, gives you access to the object it points to
   * 2. caching scenario, the lifecycle of object is determined by client code
   * 3. observer desgin pattern
   * 4. avoid shared_ptr cycle
  */
  std::shared_ptr<Investmest> sp(new Investmest());
  Investmest * sp_raw = sp.get();
  sp = nullptr; // make shared_ptr dangling
  if (sp_raw == nullptr) {
    std::cout << "raw detect nullptr" << std::endl;
  } else {
    std::cout << "raw unable to detect nullptr" << std::endl;
  }
  std::cout << (sp == nullptr) << std::endl;

  std::shared_ptr<A> a(new A());
  std::shared_ptr<B> b(new B());

  a->ptr = b;
  b->ptr = a; // this shared_ptr loop caused leak resource
  std::cout << "end of item 20" << std::endl;

  /**
   * Item 21: use std::make_unique and std::make_shared over direct "new"
   * It has the advantage of improve exception safety, generate smaller and efficient code (since it has the pointed object and control block in same memory block, i.e. only need one ptr)
   * 
   * when not to use them
   * custom deleter and pass brace initializers
   * 
   * additional for shared_ptr
   * class with custom management
   * system with very large memory and weak_ptr outlive shared_ptr
  */

  auto sp_auto = std::make_shared<Investmest>();

  /**
   * Item 22: when using Pimpl
   * 
   * What is a Pimpl (Pointer to Implementation) Idiom
   * It is used to accelerate the process of building
   * 
   * when using std::unique_ptr for Pimpl, you have to declare all compiler genertead code
   * destructor --> move constructor, move operator --> (and if the member need to be copy) --> copy constructor and copy operator
   * 
   * for std::shared_ptr do not need to do that (the reason lies in custom deleter type needed to be declared in template type of std::unique_ptr but not
   * std::shared_ptr)
  */
}