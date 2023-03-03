#include <iostream>
#include <memory>
#include <unordered_map>

class Widget {
  int id;
  public:
  Widget(int _id) : id(_id) {
    std::cout << "a Widget id " << id << " is created" << std::endl;
  }

  ~Widget() {
    std::cout << "a Widget id " << id << " is destroyed" << std::endl;
  }
};

std::unordered_map<int, std::weak_ptr<Widget>> cache;

std::shared_ptr<Widget> loadWidget(int widgetID) {
  auto objPtr = cache[widgetID].lock();

  if (objPtr == nullptr) {
    objPtr = std::make_shared<Widget>(widgetID);
    cache[widgetID] = objPtr;
  }

  return objPtr;
}

int main() {
  auto ptr = loadWidget(0);
  ptr = loadWidget(0);
  // do some computation
  ptr.reset();
  std::cout << cache[0].expired() << std::endl;
}