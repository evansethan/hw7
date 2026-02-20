#ifndef ASYNC_H
#define ASYNC_H

#include<future>
#include <numeric>
#include <thread>
#include <future>
#include <vector>



template<typename Func, typename ...Args>
auto my_async(Func f, Args... args) {

    std::paclaged_task

}

// Helper: adds a value t to the result of a future f.
// Blocks until the future is ready via f.get().
template<class T>
T accumulate_future_value(T t, std::future<T> &f)
{
	return t + f.get();
}

template<typename Iterator,typename T>
T async_accumulate(Iterator first,Iterator last,T init)
{
    //unsigned long const length=std::distance(args...); // total number of elements
    if(!length)
        return init; // nothing to accumulate, return identity value
    unsigned long const min_per_thread=25; // minimum elements per thread to avoid over-parallelizing
    // max useful threads: at most one thread per min_per_thread elements
    unsigned long const max_threads = (length+min_per_thread-1)/min_per_thread;

    // hardware_concurrency may return 0 if it doesn't choose to answer
    unsigned long const hardware_threads = std::thread::hardware_concurrency();
    // use hardware thread count, fall back to 2 if unknown, but never exceed max_threads
    unsigned long const num_threads
       = std::min(hardware_threads!=0?hardware_threads:2,max_threads);
    unsigned long const block_size=length/num_threads; // how many elements each thread handles
    std::vector<std::future<T> > futures(num_threads-1); // one future per worker thread (main thread handles last block)
    Iterator block_start=first; // tracks the start of the current block
    for(unsigned long i=0;i<(num_threads-1);++i) {
        Iterator block_end=block_start;
        std::advance(block_end,block_size); // block_end points one past this thread's last element
        // launch async task: accumulate this block starting from zero (T{})
        // result is retrieved later via futures[i].get()
        futures[i]
          = std::async(
		   std::accumulate<Iterator,T>,
		   // next line for MSVC 2010, instead of the above:
		   //static_cast<T (*)(Iterator, Iterator, T)>(std::accumulate<Iterator,T>),
               block_start,
               block_end,
               T{}); // start each block's partial sum at zero; init is folded in at the end
        block_start=block_end; // advance start to the next block
    }
    // accumulate the last block on the main thread (block_start to last),
    // then fold in all futures (blocking on each one) via std::accumulate with a lambda
	return std::accumulate
		     (futures.begin(),
			  futures.end(),
              std::accumulate(block_start, last, T()), // seed: partial sum of the last block
              [](auto &acc, auto &next) { return acc + next.get();  } // add each thread's result, blocking until ready
			  );
}

#endif



// Create a std::packaged_task wrapping f(args...)
// Extract a std::future from it via .get_future()
// Spin up a std::thread to execute the task, then call .detach() on it
// Return the future