#include <iostream>
#include <future>
#include <vector>

using namespace std::literals;

class A {
  public:
  A() = default;
  // explicit A(const A & rhs) {
  //   // not allowed
  // }
  A(const A & rhs) {}
};

bool isPrime(int x) {
    std::cout << "Calculating. Please, wait...\n";
    for (int i=2; i<x; ++i) if (x%i==0) return false;
    return true;
}

void sleep_func() {
  std::cout << "sleep task is called" << std::endl;
  std::this_thread::sleep_for(1s);
}

int f() {
  std::thread t(isPrime, 10);
  return 0;
}

class ThreadRAII {
public:
  enum class DtorAction { join, detach };           // as before

  ThreadRAII(std::thread&& t, DtorAction a)         // as before
  : action(a), t(std::move(t)) {}

  ~ThreadRAII()
  { 
    std::cout << "~ThreadRAII is called" << std::endl;
     if (t.joinable()) {                          // joinability test

      if (action == DtorAction::join) {
        std::cout << "~ThreadRAII is waiting thread to complete task" << std::endl;
        t.join();
      } else {
        t.detach();
      }
      
    }                                               // as before
  }

  ThreadRAII(ThreadRAII&&) = default;               // support
  ThreadRAII& operator=(ThreadRAII&&) = default;    // moving

  std::thread& get() { return t; }                  // as before

private:                                            // as before
  DtorAction action;
  std::thread t;  // always a good idea to have thread to be created in the last, since there might be some data members need to be initialized before thread produce correct behavior
};

std::condition_variable cv;
std::mutex m;
bool flag = false;

void notify_func() {
  {
    std::unique_lock<std::mutex> lck(m);
    flag = true;
  }
  cv.notify_one();
}

void wait_func() {
  std::cout << "waiting -----" << std::endl;
  {
    std::unique_lock<std::mutex> lck(m);
    cv.wait(lck, [] { return flag; });
  }
  std::cout << "finsihing waiting ----" << std::endl;
}

std::promise<void> p;
void react() {
  std::cout << "react is called" << std::endl;
}

void detect() {
  std::cout << "detect() is called transmitted event" << std::endl;
  p.set_value();
}

void test_main_code() {
  std::thread t([] {
    p.get_future().wait();
    react();
  });
  
  throw std::exception();
  detect();

  t.join();
}

void test_thread_raii_code() {
  ThreadRAII tr(
    std::thread([] {
      p.get_future().wait();
      react();
    }),
    ThreadRAII::DtorAction::join
  );
  throw std::exception();
  detect();
}

std::atomic<int> ac(0);
volatile int vc(0);

void increment_both() {
  ac++;
  vc++;
}

int main() {
  /**
   * Item 35: Prefer task-based API to thread based API
   * 
   * When using thread-based API, it provide no direct way to get the result of function, and when thread throw exception, the whole program terminated
   * Also, there are some issue with thread-based API that seems annoying
   * 1. thread management to avoid oversubscription (the situation software thread is more than hardware thread)
   * 
   * On the other hand, task-based lie the burden of thread management on run-time scheduler rather than user
   * 
   * However, there are still stuation you need thread based API
   * 1. need access to the API of the underlying threading implementation
   * 2. need to and are able to optimize thread usage for your application
   * 3. need to implement threading technology beyond the C++ concurrency API, e.g., thread pools on platforms where your C++ implementations don’t offer them.
  */

  std::future<bool> func_task = std::async(std::launch::deferred, isPrime,313222313);
  bool ret = func_task.get(); // the passed in function would only run if future object get is called

  auto func_async = std::async(std::launch::async, isPrime, 313222313);

  /**
   * Item 36: Specify std::launch::async if asynchronous execution is necessary
   * 
   * The default lauch policy for std::async is std::launch::deffered | std::launch::async
   * That means the behavior is non-deterministic, it bascially depend on the environment of the system
   * 
   * This would lead to infinte loop in wait loop
  */
  auto sleep_task = std::async(sleep_func); // the launch policy is not sure, it might be std::launch::deferred if there is huge amount of thread created
  while (sleep_task.wait_for(100ms) != std::future_status::ready) {
    // do stuff
  }


  f();
  while (1) {}

  /**
   * Item 37: RAII thread class
   * 
   * This item mainly discussed std::thread destructor behavior. i.e. throwing a exception, and why this is a better choice than implicit join or detach
   * Also, it discussed RAII thread class
   * 
   * call join and detached on unjoinable thread object is classified undefined behavior
   * 
   * joinable thread object would thread exception if the thread is not joined when it is out of scope
   * the design for this is becuase:
   * 1. implicit join would lead to some performance downgrade, and there might be a hanging problem (solution is to write a interruptible thread)
   * 2. implicit detached would have detached thread write to out of scope function's frame memory (hard to debug code)
   * 
   * see above RAII thread for better way to handle the problem
  */


  /**
   * Item 38: destructor behavior on task-based threading object (i.e. std::future)
   * 
   * There are two destruction behavior for std::async
   * 1. it would just destroyed the future object. It doesn’t join with anything, it doesn’t detach from anything, it doesn’t run anything
   * 2. it would do an implicit join
   * 
   * The second scenario would only occurred if the following is met:
   * 1. It refers to a shared state that was created due to a call to std::async
   * 2. The task’s launch policy is std::launch::async
   * 3. The future is the last future referring to the shared state
  */

 /**
  * Item 39: use void future on on shot event communication
  * 
  * such event are like thread need to be configured before run, etc
  * 
  * For event communication, there are two things need to be catious
  * 1. notifying thread notify before waiting thread wait, this would cause the waiting thread to be hang
  * 2. spurious wakeup, e.g. by scheduler
 */
  auto wait_task = std::async(wait_func);
  notify_func();

  // below are improveed approach
  try {
    test_main_code();
  } catch (std::exception & e) {
    std::cout << "exception caught" << std::endl;
  }

  try {
    test_thread_raii_code();
  } catch (std::exception & e) {
    std::cout << e.what() << std::endl;
  }

  std::vector<std::thread> t_vec;

  for (int i = 0; i < 10000; i++) {
    t_vec.push_back(std::move(std::thread(increment_both)));
  }

  for (int i = 0; i < t_vec.size(); i++) {
    t_vec[i].join();
  }

  std::cout << "ac: " << ac << ", vc: " << vc << std::endl;

  /**
   * Item 40: the use case for std::atomic and volatile
   * 
   * std::atomic: use for concurrent accessed memeory without mutex
   * volatile: used for data member on special memory (like mmap)
  */

  volatile int x = 0; // assume x is a mmap memory, tell compliler not to optimized out

  int y = x; // read x twice
  y = x;

  x = 10;
  x = 20;

  A a;
  A ab = a;
}