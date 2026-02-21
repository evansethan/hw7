#include "Promise.h"
#include "Future.h"
#include <iostream>
#include <thread>

int main() {
    // Basic set_value / get test
    my_promise<int> p;
    my_future<int> f = p.get_future();

    std::thread t([&]{ p.set_value(42); });
    std::cout << f.get() << "\n"; // 42
    t.join();

    // Exception test
    my_promise<int> p2;
    my_future<int> f2 = p2.get_future();

    std::thread t2([&]{
        p2.set_exception(std::make_exception_ptr(std::runtime_error("error")));
    });
    try {
        f2.get();
    } catch (const std::runtime_error& e) {
        std::cout << e.what() << "\n"; // error
    }
    t2.join();

    return 0;
}
