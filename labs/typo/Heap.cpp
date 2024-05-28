#include "Heap.h"
#include <cstring>
#include <stdexcept>

Heap::Heap(size_t capacity) : mCapacity(capacity), mCount(0) {
  mData = new Entry[capacity];
}

Heap::Heap(const Heap &other)
    : mCapacity(other.mCapacity), mCount(other.mCount) {
  mData = new Entry[mCapacity];
  for (size_t i = 0; i < mCapacity; i++) {
    mData[i] = other.mData[i];
  }
}

Heap::~Heap() { delete[] mData; }

size_t Heap::capacity() const { return mCapacity; }

size_t Heap::count() const { return mCount; }

const Heap::Entry &Heap::lookup(size_t index) const {
  if (index >= mCount) {
    throw std::out_of_range("Index out of range");
  }
  return mData[index];
}

Heap::Entry Heap::pop() {
  if (mCount == 0) {
    throw std::underflow_error("Empty heap");
  }

  Entry result = mData[0];
  mData[0] = mData[--mCount];

  size_t index = 0;
  while (true) {
    size_t left = (2 * index) + 1;
    size_t right = (2 * index) + 2;
    size_t min_index = index;

    if ((left < mCount) && (mData[left].score < mData[min_index].score)) {
      min_index = left;
    }

    if ((right < mCount) && (mData[right].score < mData[min_index].score)) {
      min_index = right;
    }

    if (min_index != index) {
      std::swap(mData[index], mData[min_index]);
      index = min_index;
    } else {
      break;
    }
  }

  return result;
}

Heap::Entry Heap::pushpop(const std::string &value, float score) {
  if (mCount == 0) {
    throw std::underflow_error("Empty heap");
  }

  if (score < mData[0].score) {
    return {value, score};
  }

  Entry top = mData[0];
  mData[0] = {value, score};

  size_t index = 0;
  while (true) {
    size_t left = (2 * index) + 1;
    size_t right = (2 * index) + 2;
    size_t min_index = index;

    if ((left < mCount) && (mData[left].score < mData[min_index].score)) {
      min_index = left;
    }

    if ((right < mCount) && (mData[right].score < mData[min_index].score)) {
      min_index = right;
    }

    if (min_index != index) {
      std::swap(mData[index], mData[min_index]);
      index = min_index;
    } else {
      break;
    }
  }

  return top;
}

void Heap::push(const std::string &value, float score) {
  if (mCount >= mCapacity) {
    throw std::overflow_error("Filled heap");
  }

  // AGGREGATE INITIALIZATION
  mData[mCount++] = {value, score};

  // BOTTOM UP PERCOLATION
  size_t index = mCount - 1;
  while (index > 0) {
    size_t parentIndex = (index - 1) / 2;
    if (mData[index].score < mData[parentIndex].score) {
      std::swap(mData[parentIndex], mData[index]);
      index = parentIndex;
    } else {
      break;
    }
  }
}

const Heap::Entry &Heap::top() const {
  if (mCount == 0) {
    throw std::underflow_error("Empty top");
  }
  return mData[0];
}
