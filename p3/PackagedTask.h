#ifndef PACKAGED_TASK_H
#define PACKAGED_TASK_H

#include <future>
#include <thread>
#include <vector>

template<typename T, typename Func>
class my_packaged_task {
public:
    std::promise<T> promise;
    Func f;
    my_packaged_task(Func func) : f(func) {};

    std::future<T> get_future() {
        return promise.get_future();
    }
    
    template<typename ...Args>
    void operator()(Args... args) {
        promise.set_value(f(args...));
    }
};


#endif