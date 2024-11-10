// CircularBuffer.hpp
#ifndef CIRCULARBUFFER_HPP
#define CIRCULARBUFFER_HPP

#include <deque>

class CircularBuffer {
public:
    CircularBuffer(size_t maxSize);
    void add(double value);
    double getSum() const;
    size_t size() const;
    std::deque<double> buffer;
    void reset();
private:
    
    size_t maxSize;
    double currentSum;
};

#endif // CIRCULARBUFFER_HPP
