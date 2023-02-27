#include <iostream>
#include <thread>
#include <exception>
#include <future>

void say_hello() {
  throw std::exception();
}

void thread_throw_except() {
  try {
    std::thread t1(say_hello);
  } catch (std::exception & e) {
    std::cout << "I get the exception from thread based" << std::endl;
  }
}

void task_throw_except() {
  try {
    auto fut = std::async(say_hello);
    fut.get();
  } catch (std::exception & e) {
    std::cout << "I get the exception from task based" << std::endl;
  }
}

int main() {
  // thread_throw_except();
  task_throw_except();
}