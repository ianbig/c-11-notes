/**
 * Conclusion: it is meaningless to do smart pointer on low-level data structure
 * Even the standard library do the implementation by raw pointer
 * Also, doing low level data structure implementation is only for algorithm exercise purpose
 * Doing it on production code is error-prone, it is smart to use the container provided by STL in production code
 * see more explanation: https://stackoverflow.com/questions/36673391/c-linked-list-using-smart-pointers
*/

#include <iostream>

class Node {
  public:
  int val;
  Node * next;
};


class LinkList {
  std::unique_ptr<Node> root;
  public:
  LinkList() : root(nullptr) {}
  void push_back() {}

};

int main() {}