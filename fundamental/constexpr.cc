
constexpr
char* func(char * sz) {
  return sz;
}

int main() {
  constexpr int csz = 10;
  constexpr auto a = csz;

  int sz = 10;
  
  func("Ian is handsome");

}