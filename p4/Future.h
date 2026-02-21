#ifndef FUTURE_H
#define FUTURE_H

#include <memory>
#include <exception>
#include <mutex>
#include <condition_variable>
#include "SharedState.h"

template<typename T>
class my_future {
public:
    std::shared_ptr<shared_state<T>> sptr;

    my_future(std::shared_ptr<shared_state<T>> sp) {
        sptr = sp;
    };

    T get() {
        std::unique_lock lock(sptr->mtx);
        sptr->cv.wait(lock, [&]{ return sptr->ready; });
        if (sptr->eptr != nullptr) {
            std::rethrow_exception(sptr->eptr);
        }
        return sptr->val;
    }

};

#endif