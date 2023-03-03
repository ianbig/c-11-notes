class Widget {
  public:
  void draw() {}
  void get() {}
  template<typename T>
  void deltemp(T * ptr) {}
};

template<>
void Widget::deltemp<int>(int *) = delete;

class NoGetWidget : public Widget {
  public:
  void get() = delete;
};

int main() {
  NoGetWidget w;
  w.get();
  
  Widget w2;
  int ptr;
  w2.deltemp<int>(&ptr);

  char cptr;
  w2.deltemp<char>(&cptr);
}