#include <iostream>


class INT {
  int data;
  public:
  ~INT() = default;

  INT & operator=(INT & rhs) {
    throw std::exception();
  }
};

class Widget {
  INT * data;
  size_t sz;
  public:
  Widget() : data(new INT[20]), sz(20) {}
  ~Widget() {
    delete [] data;
  }
  Widget & operator=(Widget & rhs) {
    if (this != &rhs) {
        Widget newData;
        for (int i = 0; i < rhs.sz; i++) {
          newData.data[i] = rhs.data[i]; // throw
        }

        data = newData.data;
        sz = rhs.sz;
    }

    return *this;
  }
};


int main () {
  Widget w1, w2;
  
  try {
    w1 = w2;
  } catch (std::exception & e) {
    
  }
}