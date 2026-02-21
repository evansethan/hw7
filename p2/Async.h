#ifndef ASYNC_H
#define ASYNC_H

#include <future>
#include <thread>
#include <vector>

template<typename Func, typename ...Args>
auto my_async(Func f, Args... args) {

    std::packaged_task<decltype(f(args...))()> pt([=]{ return f(args...); });
    auto result = pt.get_future();
    std::thread td(std::move(pt));
    td.detach();
    return result;

}
#endif