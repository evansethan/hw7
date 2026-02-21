#include "LockFreeStack.h"
#include <iostream>

int main() {
    mpcs51044::Stack s;

    s.push(10);
    s.push(20);
    s.push(30);

    std::cout << s.pop() << "\n"; // 30
    std::cout << s.pop() << "\n"; // 20
    std::cout << s.pop() << "\n"; // 10
    std::cout << s.pop() << "\n"; // 0 (empty)

    return 0;
}
