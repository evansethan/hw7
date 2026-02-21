#include "PackagedTask.h"
#include <iostream>
#include <future>
#include <thread>

int multiply(int a, int b) {
    return a * b;
}

int main() {
    my_packaged_task<int, decltype(&multiply)> task(&multiply);
    auto fut = task.get_future();
    task(3, 4);
    std::cout << fut.get() << "\n"; // 12

    return 0;
}
