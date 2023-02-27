#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>

using namespace std::literals;


std::mutex mu;
std::condition_variable cv;
bool flag(false);

void react() {
  std::unique_lock<std::mutex> lck(mu);
  std::this_thread::sleep_for(5s);
  std::cout << "react ready to wait" << std::endl;
  cv.wait(lck, [] { 
    return flag;}
  ); // lamna prevent spurious wait up
  // with wait another thing to consider is notify is send before wait
  // when there is too much threads it would result in this react thread
  // never to be waken since it get its notification way before it started
  // to wait
}

void notify() {
  std::unique_lock<std::mutex> lck(mu);
  flag = true;
  cv.notify_one();
  std::cout << "has notify thread" << std::endl;
}

int main() {
  std::thread t1(react);
  notify();
  t1.join();
}