#include <iostream>
using namespace std;

class Widget {
  public:
  int x = 20;
  virtual void display() {
    cout << "Display Widget" << endl;
  }
};

class Image {
  public:
  int y = 10;
  virtual void display() {
    cout << "Display Image" << endl;
  }
};

class ImageWidget : public Widget, public Image {
  public:
  virtual void display() {
    cout << "Display ImageWidget " << x << ", " << y << endl;
  }
};

int main() {
  Widget * widget = new ImageWidget();
  widget->display();

  Image * img = new ImageWidget();
  img->display();
}