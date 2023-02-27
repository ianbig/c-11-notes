#include <iostream>
#include <future>
#include <thread>

using namespace std::literals;

std::promise<void> p;

void thread_task() {
  std::cout << "thread in suspend state" << std::endl;
  p.get_future().wait();
  std::cout << "thread running" << std::endl;
  // do thread intended operation
}

void config() {
  std::cout << "finish thread config" << std::endl;
  p.set_value();
}


int main() {
  std::thread t(thread_task);
  std::this_thread::sleep_for(1s);
  config();
  t.join();
}