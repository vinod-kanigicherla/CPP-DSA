#ifndef FIBVEC_H
#define FIBVEC_H

#include <cstddef>
#include <stdexcept>

class FibVec {
private:
    int* fib_vector;
    size_t fCapacity;     // Current capacity (f(n))
    size_t fPrevCapacity; // Previous capacity (f(n-1))
    size_t fPrevPrevCapacity; // Previous to previous capacity (f(n-2))
    size_t fCount;

    void resizeUp();
    void resizeDown();

public:
    FibVec();
    ~FibVec();
    size_t count() const;
    size_t capacity() const;
    void insert(int val, size_t index);
    int lookup(size_t index) const;
    void push(int val);
    int pop();
    int remove(size_t index);
};

#endif
