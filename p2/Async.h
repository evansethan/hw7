#ifndef ASYNC_H
#define ASYNC_H

#include <future>
#include <thread>
#include <vector>

template<typename Func, typename ...Args>
auto my_async(Func f, Args... args) {

    std::packaged_task<std::invoke_result_t<Func,Args...>()> pt(f);
    auto result = pt.get_future();
    std::thread td(std::move(pt), args...);
    td.detach();
    return result;

}
#endif

