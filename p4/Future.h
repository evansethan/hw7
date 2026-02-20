#ifndef FUTURE_H
#define FUTURE_H

#include <memory>
#include <exception>


template<typename T, typename Func>
class my_future {
public:
    std::shared_ptr sptr;
    std::exception_ptr eptr;

    my_future() : x(x) {};

};

#endif