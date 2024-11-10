// CircularBuffer.cpp
#include "CircularBuffer.hpp"

CircularBuffer::CircularBuffer(size_t maxSize) : maxSize(maxSize), currentSum(0) {}

void CircularBuffer::add(double value) {
    buffer.push_back(value);
    currentSum += value;

    if (buffer.size() > maxSize) {
        currentSum -= buffer.front();
        buffer.pop_front();
       
    }
}

double CircularBuffer::getSum() const {
    return currentSum;
}

size_t CircularBuffer::size() const {
    return buffer.size();
}

void CircularBuffer:: reset() {
    currentSum = 0;
    buffer.clear();
}
