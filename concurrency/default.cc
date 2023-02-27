#include <iostream>
#include <thread>
#include <exception>
#include <future>

using namespace std::literals;

void sleep_func() {
  std::cout << "sleep task is called" << std::endl;
  std::this_thread::sleep_for(1s);
}

int main() {
  auto sleep_task = std::async(sleep_func); // the launch policy is not sure, it might be std::launch::deferred if there is huge amount of thread created
  while (sleep_task.wait_for(100ms) != std::future_status::ready) {
    // do stuff
  }
}