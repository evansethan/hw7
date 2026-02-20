#ifndef FUTURE_H
#define FUTURE_H

#include <memory>
#include <exception>

struct shared_state {
    std::shared_ptr sptr;
    std::exception_ptr eptr;
};


template<typename T, typename Func>
class my_future {
public:
    shared_state sstate;

    my_future() : x(x) {};

};

#endif