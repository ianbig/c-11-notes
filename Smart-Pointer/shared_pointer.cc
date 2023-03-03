#include <iostream>
#include <vector>
#include <memory>

class Widget;
std::vector<std::shared_ptr<Widget>> processed;

class Widget {
  public:
  void process() {
    processed.emplace_back(this);
  }
};

class WidgetFix;
std::vector<std::shared_ptr<WidgetFix>> processedWidgetFix;
class WidgetFix: public std::enable_shared_from_this<WidgetFix> {
  public:
  void process() {
    processedWidgetFix.emplace_back(shared_from_this());
  }
};


int main() {
  // This code create double free
  std::shared_ptr<Widget> w = std::make_shared<Widget>();
  w->process();

  std::shared_ptr<WidgetFix> wfix = std::make_shared<WidgetFix>();
  wfix->process();
  
}