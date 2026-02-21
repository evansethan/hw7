#ifndef LOCK_FREE_STACK_H
#  define LOCK_FREE_STACK_H
#include<atomic>
#include<memory>
using std::atomic;

namespace mpcs51044 {
// Linked list of integers
struct StackItem {
  StackItem(int val) : next(0), value(val) {}
  StackItem *next; // Next item, 0 if this is last
  int value;
};

struct StackHead {
  StackItem *link;      // First item, 0 if list empty
  unsigned count;      // How many times the list has changed (see lecture notes)
};

struct Stack {
  Stack();
  int pop();
  void push(int);
private:
  atomic<StackHead> head;
};

Stack::Stack()
{
  StackHead init;
  init.link = nullptr;
  init.count = 0;
  head.store(init);
}

// Push value to list
void
Stack::push(int val)
{
    StackHead expected = head.load();
    StackHead newHead;
    StackItem *newItem = new StackItem(val);
    bool succeeded = false;
    while(!succeeded) {
        newHead.link = newItem;
        newHead.link->next = expected.link;
        newHead.count = expected.count + 1;
        succeeded = head.compare_exchange_weak(expected, newHead);
    }
}

// Pop value off list
int
Stack::pop()
{
    // What the head will be if nothing messed with it
    StackHead expected = head.load();
    StackHead newHead;
    bool succeeded = false;
    while(!succeeded) {
        if(expected.link == 0) {
            return 0; // List is empty
        }
        // What the head will be after the pop
        newHead.link = expected.link->next;
        newHead.count = expected.count + 1;
        // Even if the compare_exchange fails, it updates expected.
        succeeded = head.compare_exchange_weak(expected, newHead);
    }
    int value = expected.link->value;
    delete expected.link;
    return value;
}
}
#endif