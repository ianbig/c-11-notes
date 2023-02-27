#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>

#define MAXSZ 10

template<typename T>
class Queue {
  private:
  std::condition_variable cv;
  std::mutex mtx;
  T data[MAXSZ];
  size_t sz;
  public:
  Queue(): sz(0) {}
  bool isEmpty() {
    return sz <= 0;
  }
  bool isFull() {
    return sz >= MAXSZ;
  }
  void push(T val) {
    std::unique_lock<std::mutex> lck(mtx);
    while (isFull()) {
      std::cout << "queue is full, val: " << val << " is waiting" << std::endl;
      cv.wait(lck);
    }

    data[sz] = val;
    sz++;
    std::cout << "val: " << val << " is pushed" << std::endl;
    cv.notify_all();
  }

  T pop() {
    std::unique_lock<std::mutex> lck(mtx);
    while (isEmpty()) {
      std::cout << "queue is empty" << std::endl;
      cv.wait(lck);
    }

    T val = data[--sz];
    std::cout << "val: " << val << " is poped" << std::endl;
    cv.notify_all();

    return val;
  }
};

Queue<int> qu;

void producer(int val) {
  for (int  i = 0; i < 1; i++) {
    qu.push(val);
  }
}

void consumer() {
  for (int  i = 0; i < 1; i++) {
    qu.pop();
  }
}


int main() {
  std::thread pths[10];
  for (int  i = 0; i < 10; i++) {
    pths[i] = std::thread(producer, i);
  }

  std::thread cths[10];
  for (int i = 0; i < 10; i++) {
    cths[i] = std::thread(consumer);
  }

  for (int i = 0; i < 10; i++) {
    pths[i].join();
  }

  for (int i = 0; i < 10; i++) {
    cths[i].join();
  }

}