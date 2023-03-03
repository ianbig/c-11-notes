#include <iostream>

namespace A {
    int value = 5;
}

namespace B {
    int value = 10;
}

int main() {
    using namespace A;
    using namespace B;
    std::cout << value << std::endl;
    return 0;
}

