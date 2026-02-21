#include "Async.h"
#include <iostream>
#include <future>

int add(int a, int b) {
    return a + b;
}

int main() {
    auto result = my_async(add, 3, 4);
    std::cout << result.get() << "\n"; // 7

    return 0;
}
