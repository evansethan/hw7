#ifndef PROMISE_H
#define PROMISE_H

#include <memory>
#include <exception>
#include <mutex>
#include <condition_variable>
#include "SharedState.h"
#include "Future.h"

template<typename T>
class my_promise {
public:
    std::shared_ptr<shared_state<T>> sptr;

    my_promise() {
        sptr = std::make_shared<shared_state<T>>();
    };

    my_future<T> get_future() {
        return my_future<T>(sptr);
    };

    void set_value(T val) {
        std::unique_lock lock(sptr->mtx);
        sptr->val = val;
        sptr->ready = true;
        sptr->cv.notify_all();
    }

    void set_exception(std::exception_ptr ptr) {
        std::unique_lock lock(sptr->mtx);
        sptr->eptr = ptr;
        sptr->ready = true;
        sptr->cv.notify_all();
    }

};

#endif