#include "FibVec.h"
#include <algorithm>

// Key Algorithm Functions
// copy: 3 Parameters: first sequence's first and last, second sequence's first
// copy_backward: 3 Parameters: first sequence's first and last, second sequence's last

FibVec::FibVec() {
    this->fCapacity = 1;
    this->fPrevCapacity = 1;
    this->fPrevPrevCapacity = 0;
    this->fCount = 0;
    fib_vector = new int[fCapacity];
}

FibVec::~FibVec() {
    delete[] fib_vector;
}

size_t FibVec::count() const {
    return fCount;
}

size_t FibVec::capacity() const {
    return fCapacity;
}

void FibVec::insert(int val, size_t index) {
    if (index > fCount) {
        throw std::out_of_range("Out of range");
    }
    if (fCount == fCapacity) {
        resizeUp();
    }
    
    std::copy(fib_vector + index, fib_vector + fCount, fib_vector + index + 1);
    fib_vector[index] = val;
    fCount++;
}

int FibVec::lookup(size_t index) const {
    if (index >= fCount) {
        throw std::out_of_range("Out of range");
    }
    return fib_vector[index];
}

void FibVec::push(int val) {
    if (fCount == fCapacity) {
        resizeUp();
    }
    fib_vector[fCount++] = val;
}

int FibVec::pop() {
    if (fCount == 0) {
        throw std::underflow_error("Empty vector");
    }
    int result = fib_vector[--fCount];
    if (fCount < fPrevPrevCapacity) {
        resizeDown();
    }
    return result;
}

int FibVec::remove(size_t index) {
    if (index >= fCount) {
        throw std::out_of_range("Out of range");
    }
    int removedValue = fib_vector[index];
    std::copy(fib_vector + index + 1, fib_vector + fCount, fib_vector + index);
    fCount--;
    if (fCount < fPrevPrevCapacity) {
        resizeDown();
    }
    return removedValue;
}

void FibVec::resizeUp() {
    size_t newCapacity = fCapacity + fPrevCapacity;
    int* temp = new int[newCapacity];
    std::copy(fib_vector, fib_vector + fCount, temp);
    delete[] fib_vector;
    fib_vector = temp;

    fPrevPrevCapacity = fPrevCapacity;
    fPrevCapacity = fCapacity;
    fCapacity = newCapacity;
}

void FibVec::resizeDown() {
    size_t newCapacity = fPrevCapacity;
    int* temp = new int[newCapacity];
    std::copy(fib_vector, fib_vector + fCount, temp);
    delete[] fib_vector;
    fib_vector = temp;

    fCapacity = fPrevCapacity;
    fPrevCapacity = fPrevPrevCapacity;
    fPrevPrevCapacity = fCapacity - fPrevCapacity; 
}

