#ifndef SHARED_STATE_H
#define SHARED_STATE_H

#include <memory>
#include <exception>
#include <mutex>
#include <condition_variable>

template<typename T>
struct shared_state {

    T val;
    bool ready;
    std::condition_variable cv;
    std::mutex mtx;
    std::exception_ptr eptr;

    shared_state() {
        ready = false;
    }
};

#endif