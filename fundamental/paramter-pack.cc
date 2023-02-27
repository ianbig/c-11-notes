#include <iostream>

template<typename T>
void printParam(T t)
{
    std::cout << "printParam(T t) is called" << std::endl;
    std::cout << t << std::endl;
}

template<typename T, typename... Args>
void printParam(T t, Args... args)
{
    std::cout << "printParam(T t, Args... args) is called" << std::endl;
    std::cout << t << std::endl;
    printParam(args...);
}

template<typename... Args>
void print(Args... args)
{
    std::cout << "print(Args... args) is called" << std::endl;
    printParam(args...);
}

int main()
{
    int a = 10;
    double b = 3.14159;
    char c = 'c';
    
    print(a, b, c);
    return 0;
}
