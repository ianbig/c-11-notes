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

  Widget & operator=(Widget & rhs) {
    if (this != &rhs) {
        delete [] data;
        data = new INT[rhs.sz];
        sz = rhs.sz;
        for (int i = 0; i < rhs.sz; i++) {
          try {
            data[i] = rhs.data[i]; // throw
          } catch (std::exception & e) {
            delete [] data;
            throw; // re-throw
          }
        }
    }

    return *this;
  }
};


int main () {
  Widget w1, w2;
  
  try {
    w1 = w2; // the leak happens at w2
  } catch (std::exception & e) {
    
  }
}